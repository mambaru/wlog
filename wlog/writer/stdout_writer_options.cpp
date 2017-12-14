#include "stdout_writer_options.hpp"

namespace wlog{

stdout_writer_options& stdout_writer_options::operator <<= (const stdout_writer_options& other)
{
  stdout_writer_options& self = *this;
  if ( self.name.empty() ) self.name = other.name;
  if ( self.name=="#" ) self.name.clear();
  if ( self.sync==-1 ) self.sync = other.sync;
  return self;
}

}
