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
  
/*  
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
*/

file_writer::~file_writer()
{
  _flog.close();
}
  

file_writer::file_writer(const formatter_fun& formatter, const options& opt, const handlers& hdlr)
  : _contex(formatter, opt, hdlr)
{
  
  time_t file_time = 0;
  struct stat t_stat;
  if ( 0 == stat(_contex.options.path.c_str(), &t_stat) )
  {
    file_time  = t_stat.st_ctime;
  }

  if ( _contex.options.time_limit > 0 )
  {
    _contex.rotate_time = ( file_time ==0 ? time(0) : file_time) + _contex.options.time_limit;
  }
  
  if ( _contex.options.startup_rotate > 0 && _contex.options.rotation == 0  )
  {
    _flog.open( _contex.options.path);
  }
  else
    _flog.open( _contex.options.path, std::ios_base::app );
  
  if ( !this->rotate_if_(_flog)  )
  {
    if ( file_time!=0 && _contex.options.startup_rotate > 0 )
      this->rotate_(_flog);
  }
  
  if ( _contex.options.sync != 0)
    _flog.close();
}

void file_writer::operator()(
  const time_point& tp,
  const std::string& name, 
  const std::string& ident,
  const std::string& str
)
{
  if ( _contex.options.sync != 0 )
    _flog.open( _contex.options.path, std::ios_base::app );
  
  this->write_(_flog, tp, name, ident, str);
  
  if ( _contex.options.sync != 0 )
  {
    _flog.flush();
    _flog.close();
  }
  
    
}

void file_writer::rotate_( std::ofstream& oflog)
{
  oflog.close();
  
  std::string old_name;
  if ( _contex.options.rotation > 0 )
  {
    if ( _contex.rotation_counter >= size_t(_contex.options.rotation)  )
    {
      std::string del_file = _contex.options.path + ".old-" 
                             + std::to_string(_contex.rotation_counter - size_t(_contex.options.rotation) );
      if ( 0!=std::remove( del_file.c_str() ) )
      {
        perror( (std::string("Error remove old log file (") + del_file +")").c_str() );
      }
    }

    old_name = _contex.options.path + ".old-" + std::to_string(_contex.rotation_counter);
    if ( 0 != std::rename(_contex.options.path.c_str(), old_name.c_str() ) )
    {
      perror( "Error renaming current log file" );
    }
  }
  
  oflog.open(_contex.options.path);
    
  if ( _contex.options.rotation > 0 )
  {
    oflog << "Previous log: " << old_name << std::endl;
    ++_contex.rotation_counter;
  }

  //oflog.open(_opt.path);
}

bool file_writer::rotate_if_( std::ofstream& oflog)
{
  bool rotated = false;
  if ( _contex.options.size_limit > 0 || _contex.options.time_limit > 0 )
  {
    time_t now = time(0);
    size_t size = 0;
    std::ofstream::pos_type pos = oflog.tellp();
    if ( pos >= 0 )
      size = size_t(pos);

    bool by_size = _contex.options.size_limit > 0 && size > size_t(_contex.options.size_limit);
    bool by_time = _contex.options.time_limit > 0 && now > _contex.rotate_time;
    
    if ( by_size || by_time )
    {
      _contex.summary_size += size;
      
      oflog << "---------------- truncate with " << size
            << " summary size "    << _contex.summary_size
            << " ( start time: "   << "_starttime" << ")"
            << " ----------------" << std::endl;

      this->rotate_(oflog);
      rotated = true;
      _contex.rotate_time = now + _contex.options.time_limit;
      
      oflog << "---------------- truncate with " << size
            << " summary size "    << _contex.summary_size
            << " ( start time: "   << "_starttime" << ")"
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
  
  if ( _contex.formatter != nullptr )
  {
    std::stringstream ss;
    _contex.formatter(ss, tp, name, ident, str);
    oflog << ss.str();
  }
  else
    oflog << name << " " << ident << " " << str;
}

void file_writer::write_head(std::ostream& os, const context_type& contex)
{
  if ( contex.path_list.empty() )
    return;
  
  time_t ts = time_point::clock::to_time_t(contex.start_time);
  struct tm t1;
  localtime_r(&ts, &t1);
  char buf[100]={0};
  std::strftime(buf, 100, "%c", &t1);

  os << "! ---------------- rotated ----------------" << std::endl
     << "! Start time: "    << buf  << std::endl
     << "! Summary size: "  << contex.summary_size << std::endl
     << "! Total Rotated: " << contex.rotation_counter << std::endl
     << "! Previous log: "  << contex.path_list.back()  << std::endl
     << "! -----------------------------------------" << std::endl;
     
}
  
void file_writer::write_footer(std::ostream& os, const context_type& context)
{
  file_writer::write_head(os, context);
}


}
