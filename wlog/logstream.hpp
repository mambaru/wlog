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

class logstream final
{
public:
  ~logstream();
  
  logstream(const logstream& ll) = delete;
  
  logstream& operator = (logstream& ll) = delete;

  logstream& operator = (logstream&& ll) = delete;

  logstream(logstream&& ll);
  
  logstream(std::mutex& m, const std::string& name, const std::string& ident, const logger_fun& writer);
  
  std::string str() const;
  
  void write();

  std::ostream& operator<< (std::ios& (*pf)(std::ios&));
  
  std::ostream& operator<< (std::ios_base& (*pf)(std::ios_base&));
  
  std::ostream& operator<< (std::ostream& (*pf)(std::ostream&));
  
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
  const logger_fun& writer_;
  std::stringstream _ss;
};


class stdout_stream final
{
public:
  ~stdout_stream();
  
  stdout_stream(const stdout_stream& ll) = delete;
  
  stdout_stream& operator = (stdout_stream& ll) = delete;

  stdout_stream& operator = (stdout_stream&& ll) = delete;

  stdout_stream(stdout_stream&& ll);
  
  stdout_stream(std::mutex& m, std::ostream& writer);
  
  std::ostream& operator<< (std::ios& (*pf)(std::ios&));
  
  std::ostream& operator<< (std::ios_base& (*pf)(std::ios_base&));
  
  std::ostream& operator<< (std::ostream& (*pf)(std::ostream&));
  
  template<typename T>
  std::stringstream& operator << ( const T& arg)
  {
    _ss << arg;
    return _ss;
  }

private:
  std::mutex& _mutex;
  std::ostream& _out;
  std::stringstream _ss;
};

}
