//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logger/file_logger_options.hpp>
#include <wlog/logger/stdout_logger_options.hpp>
#include <wlog/logger/syslog_logger_options.hpp>
#include <set>

namespace wlog{
  
struct basic_logger_options: file_logger_options
{
  stdout_logger_options stdout;
  syslog_logger_options syslog;
  
  std::set<std::string> allow;
  std::set<std::string> deny;
  
  basic_logger_options& operator <<= (const basic_logger_options& other);
};

}
