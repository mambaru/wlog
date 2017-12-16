#include "stdout_writer_options.hpp"

namespace wlog{

void stdout_writer_options::upgrade(const stdout_writer_options& other)
{
  stdout_writer_options& self = *this;
  if ( self.name.empty() ) self.name = other.name;
  if ( self.sync==-1 ) self.sync = other.sync;
}

void stdout_writer_options::finalize()
{
  stdout_writer_options& self = *this;
  if ( self.name.empty() ) self.name = "cout";
  if ( self.name=="#" ) self.name.clear();
  if ( self.sync==-1 ) self.sync = 0;
  
}

}
