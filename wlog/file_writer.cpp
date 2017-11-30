//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "file_writer.hpp"
#include "aux.hpp"

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

  

file_writer::file_writer(const std::string& path, size_t limit, bool save_old)
  : _path(path)
  , _limit(limit)
  , _save_old(save_old)
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
  _summary = std::move(other._summary);
  _starttime = std::move(other._starttime);
  _mutex = std::move(other._mutex);
}

file_writer::file_writer(const file_writer& other)
  : _path(other._path)
  , _limit(other._limit)
  , _save_old(other._save_old)
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
      oflog.close();
      if ( _save_old )
      {
        if ( 0 != std::rename(_path.c_str(), (_path + ".old").c_str() ) )
        {
          perror( "Error renaming current log file" );
        }
      }
      
      oflog.open(_path);
      oflog << "---------------- truncate with " << size 
            << " summary size " << _summary 
            << " ( start time: " << _starttime << ")"
            << " ----------------" << std::endl;
    }
  }
  oflog << str;
  oflog.flush();
  oflog.close();
}

}
