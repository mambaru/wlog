#include "basic_logger_options.hpp"

namespace wlog{
  
void basic_logger_options::upgrade(const basic_logger_options& other)
{
  file_logger_options::upgrade( static_cast<const file_logger_options&>(other) );
  this->stdout.upgrade( other.stdout );
  static_cast<formatter_options&>(this->stdout).upgrade( static_cast<const formatter_options&>(other) );
  this->syslog.upgrade(other.syslog);
 }

void basic_logger_options::finalize()
{
  file_logger_options::finalize();
  this->stdout.finalize();
  this->syslog.finalize();
}


}
