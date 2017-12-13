//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/formatter/formatter_options.hpp>
#include <wlog/writer/syslog_writer_options.hpp>

namespace wlog{
  
struct syslog_logger_options: syslog_writer_options{};

inline syslog_logger_options& operator <<= (syslog_logger_options& self, const syslog_logger_options& other)
{
  static_cast<syslog_writer_options&>(self) <<= static_cast<const syslog_writer_options&>(other);
  return self;
}


}
