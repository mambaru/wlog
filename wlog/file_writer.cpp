//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "file_writer.hpp"

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <cstdio>

//#include <boost/filesystem.hpp>

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
  

file_writer::file_writer(const formatter_fun& formatter, const std::string& path, bool sync, long limit, long save_old)
  : _formatter(formatter)
  , _path(path)
  , _sync(sync)
  , _limit(limit > 0 ? limit : 0)
  , _save_old(save_old > 0 ? save_old : 0)
  , _save_count(0)
  , _summary(0)
  , _starttime( mkdate() )
{
  _oflog.open( _path, std::ios_base::app );
  if (_save_old != 0 )
    this->save_old_(_oflog, 0);
  if ( _sync )
    _oflog.close();
}

void file_writer::operator()(
  const time_point& tp,
  const std::string& name, 
  const std::string& ident,
  const std::string& str
)
{
  //std::lock_guard<mutex_type> lk(_mutex);
  
  if ( _sync )
  {
    std::ofstream oflog( _path, std::ios_base::app );
    this->write_(oflog, tp, name, ident, str);
    oflog.flush();
    oflog.close();
  }
  else
    this->write_( _oflog, tp, name, ident, str );
    
}


void file_writer::save_old_( std::ofstream& oflog, long limit)
{
  std::ofstream::pos_type pos = oflog.tellp();
  if ( pos!=static_cast<std::ofstream::pos_type>(-1) && pos > limit )
  {
    if ( limit > 0)
    {
      _summary += pos;
      oflog << "---------------- truncate with " << pos
            << " summary size " << _summary 
            << " ( start time: " << _starttime << ")"
            << " ----------------" << std::endl;
    }
    oflog.close();
    std::string old_name;
    if ( _save_old > 0 )
    {
      if ( _save_count >= _save_old  )
      {
        std::string del_file = _path + ".old-" + std::to_string(_save_count - _save_old);
        if ( 0!=std::remove( del_file.c_str() ) )
        {
          perror( (std::string("Error remove old log file (") + del_file +")").c_str() );
        }
      }

      old_name = _path + ".old-" + std::to_string(_save_count);
      if ( 0 != std::rename(_path.c_str(), old_name.c_str() ) )
      {
        perror( "Error renaming current log file" );
      }
    }
    oflog.open(_path);
    if ( limit > 0 )
    {
      oflog << "---------------- truncate with " << pos 
            << " summary size "    << _summary 
            << " ( start time: "   << _starttime << ")"
            << " ----------------" << std::endl;
    }
    if ( _save_old != 0 )
    {
      oflog << "Previous log: " << old_name << std::endl;
      ++_save_count;
    }
  }
}

void file_writer::write_(  
  std::ofstream& oflog,
  const time_point& tp,
  const std::string& name, 
  const std::string& ident,
  const std::string& str
)
{
  //std::ofstream oflog( _path, std::ios_base::app );
  //std::ofstream& oflog = _oflog;
  if ( !oflog ) return;
  
  if ( _limit > 0 )
  {
    this->save_old_(_oflog, _limit);
  }
  //oflog << str;
  if ( _formatter != nullptr )
    _formatter(oflog, tp, name, ident, str);
  else
    oflog << name << " " << ident << " " << str;

  //oflog.flush();
  //oflog.close();
}

}
