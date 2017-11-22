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
  const std::string& str)
> logger_fun;
  
}
