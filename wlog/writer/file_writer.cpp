//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "file_writer.hpp"

#include <sys/stat.h>
#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>

namespace wlog{
  
  
namespace{

  std::string mkdate()
  {
    time_t ts = time(0);
    struct tm t1;
    localtime_r(&ts, &t1);
    char buf[100];
    int sz = strftime(buf,sizeof(buf), "%Y-%m-%d %H:%M:%S",&t1);
    return std::string(buf, static_cast<std::string::size_type>(sz) );
  }
}


file_writer::~file_writer()
{
  _oflog.close();
}
  

file_writer::file_writer(const formatter_fun& formatter, const options& opt, const handlers& hdlr)
  : _formatter(formatter)
  , _opt(opt)
  , _handlers(hdlr)
  , _save_count(0)
  , _summary(0)
  , _rotate_time(0)
  , _starttime( mkdate() )
{
  if ( _opt.sync == -1 ) _opt.sync = 1;
  if ( _opt.startup_rotate == -1 ) _opt.startup_rotate = 0;
  if ( _opt.size_limit == -1 ) _opt.size_limit = 0;
  if ( _opt.time_limit == -1 ) _opt.time_limit = 0;
  if ( _opt.rotation   == -1 ) _opt.rotation = 0;

  time_t file_time = 0;
  struct stat t_stat;
  if ( 0 == stat(_opt.path.c_str(), &t_stat) )
  {
    file_time  = t_stat.st_ctime;
  }

  if ( _opt.time_limit > 0 )
  {
    _rotate_time = ( file_time ==0 ? time(0) : file_time) + _opt.time_limit;
  }
  
  if ( _opt.startup_rotate > 0 && _opt.rotation == 0  )
    _oflog.open( _opt.path);
  else
    _oflog.open( _opt.path, std::ios_base::app );
  
  if ( !this->rotate_if_(_oflog)  )
  {
    if ( file_time!=0 && _opt.startup_rotate > 0 )
      this->rotate_(_oflog);
  }
  
  if ( _opt.sync != 0)
    _oflog.close();
}

void file_writer::operator()(
  const time_point& tp,
  const std::string& name, 
  const std::string& ident,
  const std::string& str
)
{
  if ( _opt.sync != 0 )
  {
    std::ofstream oflog( _opt.path, std::ios_base::app );
    this->write_(oflog, tp, name, ident, str);
    oflog.flush();
    oflog.close();
  }
  else
    this->write_( _oflog, tp, name, ident, str );
    
}

void file_writer::rotate_( std::ofstream& oflog)
{
  oflog.close();
  
  std::string old_name;
  if ( _opt.rotation > 0 )
  {
    if ( _save_count >= _opt.rotation  )
    {
      std::string del_file = _opt.path + ".old-" + std::to_string(_save_count - _opt.rotation);
      if ( 0!=std::remove( del_file.c_str() ) )
      {
        perror( (std::string("Error remove old log file (") + del_file +")").c_str() );
      }
    }

    old_name = _opt.path + ".old-" + std::to_string(_save_count);
    if ( 0 != std::rename(_opt.path.c_str(), old_name.c_str() ) )
    {
      perror( "Error renaming current log file" );
    }
  }
  
  oflog.open(_opt.path);
    
  if ( _opt.rotation > 0 )
  {
    oflog << "Previous log: " << old_name << std::endl;
    ++_save_count;
  }

  //oflog.open(_opt.path);
}

bool file_writer::rotate_if_( std::ofstream& oflog)
{
  bool rotated = false;
  if ( _opt.size_limit > 0 || _opt.time_limit > 0 )
  {
    time_t now = time(0);
    long size = 0;
    std::ofstream::pos_type pos = oflog.tellp();
    if ( pos!=static_cast<std::ofstream::pos_type>(-1) )
      size = pos;

    bool by_size = _opt.size_limit > 0 && size > _opt.size_limit;
    bool by_time = _opt.time_limit > 0 && now > _rotate_time;
    
    if ( by_size || by_time )
    {
      _summary += pos;
      
      oflog << "---------------- truncate with " << pos
            << " summary size "    << _summary 
            << " ( start time: "   << _starttime << ")"
            << " ----------------" << std::endl;

      this->rotate_(oflog);
      rotated = true;
      _rotate_time = now + _opt.time_limit;
      
      oflog << "---------------- truncate with " << pos 
            << " summary size "    << _summary 
            << " ( start time: "   << _starttime << ")"
            << " ----------------" << std::endl;
    }
  }
  return rotated;
}

void file_writer::write_(  
  std::ofstream& oflog,
  const time_point& tp,
  const std::string& name, 
  const std::string& ident,
  const std::string& str
)
{
  if ( !oflog ) return;
  
  this->rotate_if_(oflog);
  
  if ( _formatter != nullptr )
  {
    std::stringstream ss;
    _formatter(ss, tp, name, ident, str);
    oflog << ss.str();
  }
  else
    oflog << name << " " << ident << " " << str;

}

}