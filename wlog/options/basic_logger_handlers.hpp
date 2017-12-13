//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logger_fun.hpp>

namespace wlog{
  
struct basic_logger_handlers
{
  formatter_fun file_formatter;
  formatter_fun stdout_formatter;
  formatter_fun syslog_formatter;
  
  writer_fun file_writer;
  writer_fun stdout_writer;
  writer_fun syslog_writer;
};

inline basic_logger_handlers& operator <<= (basic_logger_handlers& self, const basic_logger_handlers& other)
{
  if ( self.file_formatter==nullptr ) self.file_formatter = other.file_formatter;
  if ( self.stdout_formatter==nullptr ) self.stdout_formatter = other.stdout_formatter;
  if ( self.syslog_formatter==nullptr ) self.syslog_formatter = other.syslog_formatter;
  
  if ( self.file_writer==nullptr ) self.file_writer = other.file_writer;
  if ( self.stdout_writer==nullptr ) self.stdout_writer = other.stdout_writer;
  if ( self.stdout_writer==nullptr ) self.stdout_writer = other.stdout_writer;
  return self;
}

}
