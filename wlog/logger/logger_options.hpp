//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logger/basic_logger_options.hpp>
#include <wlog/logger/custom_logger_options.hpp>
#include <string>
#include <list>

namespace wlog{
  
struct logger_options: basic_logger_options
{
  typedef std::vector<custom_logger_options> customize_list;
  customize_list customize;

  void upgrade(const logger_options& other);
  void finalize();
};


}
