//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <functional>
#include <string>
#include <chrono>

namespace wlog{

typedef std::chrono::system_clock::time_point time_point;

typedef std::function<void(
  const time_point& tp,
  const std::string& name, 
  const std::string& ident,
  const std::string& str
)> logger_fun;

typedef std::function<void(
  std::ostream& os,
  const time_point& tp,
  const std::string& name, 
  const std::string& ident,
  const std::string& str
)> formatter_fun;

typedef std::function<void(
  std::ostream& os,
  const time_point& tp
)> datetime_formatter_fun;



typedef std::function<void(
  const time_point& tp,
  const std::string& name, 
  const std::string& ident,
  const std::string& str
)> writer_fun;

//typedef std::function<void(const std::string& type, const std::string& str)> syslog_fun;

typedef std::function<void(
  const time_point& tp,
  const std::string& name, 
  const std::string& ident,
  const std::string& str)
> after_fun;

}
