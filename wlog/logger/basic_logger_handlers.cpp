#include "basic_logger_handlers.hpp"
#include <algorithm>


namespace wlog{
  
void basic_logger_handlers::upgrade(const basic_logger_handlers& other)
{
  formatter_handlers::upgrade(static_cast<const formatter_handlers& >(other) );
  
  basic_logger_handlers& self = *this;
  
  if ( self.file_formatter==nullptr ) self.file_formatter = other.file_formatter;
  if ( self.stdout_formatter==nullptr ) self.stdout_formatter = other.stdout_formatter;
  if ( self.syslog_formatter==nullptr ) self.syslog_formatter = other.syslog_formatter;
  
  if ( self.file_writer==nullptr ) self.file_writer = other.file_writer;
  if ( self.stdout_writer==nullptr ) self.stdout_writer = other.stdout_writer;
  if ( self.stdout_writer==nullptr ) self.stdout_writer = other.stdout_writer;
  std::copy( other.after.begin(), other.after.end(), std::back_inserter(self.after) );
}

}
