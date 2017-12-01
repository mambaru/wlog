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

  

file_writer::file_writer(const std::string& path, size_t limit, int save_old)
  : _path(path)
  , _limit(limit)
  , _save_old(save_old)
  , _save_count(0)
  , _summary(0)
  , _starttime( mkdate() )
  , _mutex(std::make_shared<mutex_type>() )
{
}

file_writer::file_writer(file_writer&& other)
{
  _path = std::move(other._path);
  _limit = std::move(other._limit);
  _save_old = std::move(other._save_old);
  _save_count = std::move(other._save_count);
  _summary = std::move(other._summary);
  _starttime = std::move(other._starttime);
  _mutex = std::move(other._mutex);
}

file_writer::file_writer(const file_writer& other)
  : _path(other._path)
  , _limit(other._limit)
  , _save_old(other._save_old)
  , _save_count(other._save_count)
  , _summary(other._summary)
  , _starttime(other._starttime)
  , _mutex(other._mutex)
{
}

void file_writer::operator()( const std::string& str)
{
  std::lock_guard<mutex_type> lk(*_mutex);
  std::ofstream oflog( _path, std::ios_base::app );
  if ( !oflog ) return;
  
  if ( _limit > 0 )
  {
    std::ofstream::pos_type pos = oflog.tellp();
    size_t size = static_cast<size_t>(pos);
    if ( pos!=static_cast<std::ofstream::pos_type>(-1) && size > _limit )
    {
      _summary += size;
      oflog << "---------------- truncate with " << size 
            << " summary size " << _summary 
            << " ( start time: " << _starttime << ")"
            << " ----------------" << std::endl;
      oflog.close();
      std::string old_name;
      if ( _save_old != 0 )
      {
        if ( _save_count >= _save_old  )
        {
          std::string del_file = _path + ".old-" + std::to_string(_save_count - _save_old);
          //std::cout << "del:" << del_file << std::endl;
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
      oflog << "---------------- truncate with " << size 
            << " summary size " << _summary 
            << " ( start time: " << _starttime << ")"
            << " ----------------" << std::endl;
      if ( _save_old != 0 )
      {
        oflog << "Previous log: " << old_name << std::endl;
        ++_save_count;
      }
    }
  }
  oflog << str;
  oflog.flush();
  oflog.close();
}

}
