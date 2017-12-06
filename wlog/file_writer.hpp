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

class file_writer final
{
public:
  ~file_writer();
  file_writer(const formatter_fun& formatter, const std::string& path, bool sync, long limit, long save_old);
  void operator()(  
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  );
  
private:
  void write_(  
    std::ofstream& oflog,
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  );
  
  void save_old_( std::ofstream& oflog, long limit);

  formatter_fun _formatter;
  typedef std::mutex mutex_type;
  const std::string _path;
  const bool _sync;
  const long _limit;
  const int _save_old;
  long _save_count;
  long _summary;
  const std::string _starttime;
  //mutex_type _mutex;
  std::ofstream _oflog;
};

}
