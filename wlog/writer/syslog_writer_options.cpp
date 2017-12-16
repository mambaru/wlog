#include "syslog_writer_options.hpp"

namespace wlog{

void syslog_writer_options::upgrade(const syslog_writer_options& other)
{
  syslog_writer_options& self = *this;
  if ( self.name.empty() ) self.name = other.name;
}

void syslog_writer_options::finalize()
{
  syslog_writer_options& self = *this;
  if ( self.name=="#" ) self.name.clear();
}

}
