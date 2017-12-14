#include "syslog_logger_options.hpp"

namespace wlog{
  
syslog_logger_options& syslog_logger_options::operator <<= (const syslog_logger_options& other)
{
  syslog_logger_options& self = *this;
  static_cast<syslog_writer_options&>(self) <<= static_cast<const syslog_writer_options&>(other);
  return self;
}
  
}
