#include "syslog_writer_options.hpp"

namespace wlog{

void syslog_writer_options::upgrade(const syslog_writer_options& other)
{
  if ( this->name.empty() ) this->name = other.name;
}

void syslog_writer_options::finalize()
{
  if ( this->name=="#" ) this->name.clear();
}

}
