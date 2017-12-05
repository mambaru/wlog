//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <mutex>
#include <memory>
#include <wlog/logger_fun.hpp>
#include <fstream>

namespace wlog{

class file_writer
{
public:
  
  file_writer(const std::string& path, bool sync, long limit, int save_old);
  void operator()(  
    const formatter_fun& fmt,
    const char* name, 
    const char* ident,
    const std::string& str
  );
  
private:
  void write_(  
    std::ofstream& oflog,
    const formatter_fun& fmt,
    const char* name, 
    const char* ident,
    const std::string& str
  );
  
  void save_old_( std::ofstream& oflog, long limit);
  

  typedef std::mutex mutex_type;
  const std::string _path;
  const bool _sync;
  const long _limit;
  const int _save_old;
  int _save_count;
  long _summary;
  const std::string _starttime;
  mutable std::shared_ptr<mutex_type> _mutex;
  std::ofstream _oflog;
};

}
