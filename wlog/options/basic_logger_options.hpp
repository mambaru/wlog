//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/options/file_logger_options.hpp>
#include <wlog/options/stdout_logger_options.hpp>
#include <wlog/options/syslog_logger_options.hpp>
#include <set>

namespace wlog{
  
struct basic_logger_options: file_logger_options
{
  stdout_logger_options stdout;
  syslog_logger_options syslog;
  
  std::set<std::string> allow;
  std::set<std::string> deny;
};

inline basic_logger_options& operator <<= (basic_logger_options& self, const basic_logger_options& other)
{
  static_cast<file_logger_options&>(self) <<= static_cast<const file_logger_options&>(other);
  self.stdout <<= other.stdout;
  self.stdout <<= static_cast<const formatter_options&>(other);
  if ( self.stdout.sync == -1 ) self.stdout.sync = self.sync;
  if ( self.stdout.name=="#" ) self.stdout.name.clear();
  self.syslog <<= other.syslog;
  if ( self.syslog.name=="#" ) self.syslog.name.clear();
  return self;
}


}
