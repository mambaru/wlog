#include "file_writer_options.hpp"

namespace wlog{

void file_writer_options::upgrade(const file_writer_options& other)
{
  file_writer_options& self = *this;
  
  if ( self.path.empty() ) self.path = other.path;
  if ( self.sync==-1 ) self.sync = other.sync;
  if ( self.startup_rotate==-1 ) self.startup_rotate = other.startup_rotate;
  if ( self.size_limit==-1 )     self.size_limit = other.size_limit;
  if ( self.time_limit==-1 )     self.time_limit = other.time_limit;
  if ( self.rotation==-1 )       self.rotation = other.rotation;
}

void file_writer_options::finalize()
{
  file_writer_options& self = *this;
  if ( self.path=="#" ) self.path.clear();
  if ( self.sync==-1 ) self.sync = 1;
  if ( self.startup_rotate==-1 ) self.startup_rotate = 0;
  if ( self.size_limit==-1 )     self.size_limit = 0;
  if ( self.time_limit==-1 )     self.time_limit = 0;
  if ( self.rotation==-1 )       self.rotation = 0;

}


}
