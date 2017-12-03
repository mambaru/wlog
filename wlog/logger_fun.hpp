//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <functional>
#include <string>

namespace wlog{
  
typedef std::function<bool(
  const std::string& name, 
  const std::string& type, 
  const std::string& str
)> logger_fun;

typedef std::function<void(
  std::ostream& os,
  const std::string& name, 
  const std::string& type, 
  const std::string& str
)> formatter_fun;

typedef std::function<void(
  const formatter_fun& fmt,
  const std::string& name, 
  const std::string& type, 
  const std::string& str
)> writer_fun;

//typedef std::function<void(const std::string& type, const std::string& str)> syslog_fun;

typedef std::function<void(
  const std::string& name, 
  const std::string& type, 
  const std::string& str)
> after_fun;

}
