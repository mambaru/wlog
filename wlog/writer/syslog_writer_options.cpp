#include "syslog_writer_options.hpp"

namespace wlog{

syslog_writer_options& syslog_writer_options::operator <<= (const syslog_writer_options& other)
{
  syslog_writer_options& self = *this;
  if ( self.name.empty() ) self.name = other.name;
  if ( self.name=="#" ) self.name.clear();
  return self;
}

}
