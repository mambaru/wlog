#include "basic_logger_options.hpp"

namespace wlog{
  
basic_logger_options& basic_logger_options::operator <<= (const basic_logger_options& other)
{
  basic_logger_options& self = *this;
  static_cast<file_logger_options&>(self) <<= static_cast<const file_logger_options&>(other);
  self.stdout <<= other.stdout;
  //self.stdout <<= static_cast<const formatter_options&>(other);
  if ( self.stdout.sync == -1 ) self.stdout.sync = self.sync;
  if ( self.stdout.name=="#" ) self.stdout.name.clear();
  self.syslog <<= other.syslog;
  if ( self.syslog.name=="#" ) self.syslog.name.clear();
  return self;
}

}
