//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logger_fun.hpp>
#include <wlog/formatter/formatter_handlers.hpp>
#include <vector>

namespace wlog{
  
struct basic_logger_handlers: formatter_handlers
{
  formatter_fun file_formatter;
  formatter_fun stdout_formatter;
  formatter_fun syslog_formatter;
  
  writer_fun file_writer;
  writer_fun stdout_writer;
  writer_fun syslog_writer;
  
  std::vector<after_fun> after;

  void upgrade (const basic_logger_handlers& other);

};


}
