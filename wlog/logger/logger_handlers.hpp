//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logger/basic_logger_handlers.hpp>
#include <map>
#include <string>

namespace wlog{
  
struct logger_handlers: basic_logger_handlers
{
 typedef std::map<std::string, basic_logger_handlers> customize_map;
 customize_map customize;

  void upgrade();
};

}
