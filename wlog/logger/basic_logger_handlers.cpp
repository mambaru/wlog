#include "basic_logger_handlers.hpp"
#include <algorithm>


namespace wlog{
  
void basic_logger_handlers::upgrade(const basic_logger_handlers& other)
{
  formatter_handlers::upgrade(static_cast<const formatter_handlers& >(other) );
  
  if ( this->file_formatter==nullptr ) this->file_formatter = other.file_formatter;
  if ( this->stdout_formatter==nullptr ) this->stdout_formatter = other.stdout_formatter;
  if ( this->syslog_formatter==nullptr ) this->syslog_formatter = other.syslog_formatter;
  
  if ( this->file_writer==nullptr ) this->file_writer = other.file_writer;
  if ( this->stdout_writer==nullptr ) this->stdout_writer = other.stdout_writer;
  if ( this->stdout_writer==nullptr ) this->stdout_writer = other.stdout_writer;
  std::copy( other.after.begin(), other.after.end(), std::back_inserter(this->after) );
}

}
