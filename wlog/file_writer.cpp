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
#include <boost/filesystem.hpp>

namespace wlog{
  
namespace{

  std::string mkdate()
  {
    time_t ts = time(0);
    struct tm t1;
    localtime_r(&ts, &t1);
    char buf[100];
    int sz = strftime(buf,sizeof(buf), "%Y-%m-%d %H:%M:%S",&t1);
    return std::string(buf,sz);
  }
}

  

file_writer::file_writer(const std::string& path, size_t limit, bool save_old)
  : _path(path)
  , _limit(limit)
  , _save_old(save_old)
  , _summary(0)
  , _starttime( mkdate() )
{
}

void file_writer::write( const std::string& str)
{
  std::lock_guard<mutex_type> lk(_mutex);
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
        boost::system::error_code ec;
        boost::filesystem::rename( _path, _path + ".old", ec);
        if ( ec )
        {
          std::cerr << "_conf.limit=" <<  _limit << " size=" << size << std::endl;
          std::cerr << _path << "->" << _path + ".old" << std::endl;
          std::cerr << ec.message() << std::endl;
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
