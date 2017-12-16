#include "syslog_logger_options.hpp"

namespace wlog{
  
void syslog_logger_options::upgrade(const syslog_logger_options& other)
{
  static_cast<syslog_writer_options&>(*this).upgrade( static_cast<const syslog_writer_options&>(other) );
}

void syslog_logger_options::finalize()
{
  static_cast<syslog_writer_options&>(*this).finalize();
}
  
}
