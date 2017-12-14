//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logger/basic_logger_options.hpp>
#include <string>
#include <map>

namespace wlog{
  
struct logger_options: basic_logger_options
{
  typedef std::map<std::string, basic_logger_options> customize_map;
  customize_map customize;
  
  logger_options();
  void upgrade();
};


}
