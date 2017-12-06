//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logger_fun.hpp>
#include <sstream>
#include <string>
#include <memory>
#include <mutex>

namespace wlog{

class logstream
{
public:
  ~logstream();
  
  logstream(const logstream& ll) = delete;
  
  logstream& operator = (logstream& ll) = delete;
  
  logstream(logstream&& ll) = default;

  logstream& operator = (logstream&& ll) = delete;
  
  logstream(std::mutex& m, const std::string& name, const std::string& ident, const logger_fun& writer);
  
  std::string str() const;
  
  bool write();

  std::ostream& operator<< (std::ios& (*pf)(std::ios&))
  {
    _ss << pf;
    return _ss;
  }
  
  std::ostream& operator<< (std::ios_base& (*pf)(std::ios_base&))
  {
    _ss << pf;
    return _ss;
  }

  std::ostream& operator<< (std::ostream& (*pf)(std::ostream&))
  {
    _ss << pf;
    return _ss;
  }
  
  template<typename T>
  std::stringstream& operator << ( const T& arg)
  {
    _ss << arg;
    return _ss;
  }

private:
  std::mutex& _mutex;
  const time_point _tp;
  const std::string& _name;
  const std::string& _ident;
  std::stringstream _ss;
  const logger_fun& writer_;
};

}
