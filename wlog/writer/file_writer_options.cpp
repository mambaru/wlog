#include "file_writer_options.hpp"

namespace wlog{

void file_writer_options::upgrade(const file_writer_options& other)
{
  if ( this->sync==-1 ) this->sync = other.sync;
  if ( this->path.empty() ) this->path = other.path;
  if ( this->startup_rotate==-1 ) this->startup_rotate = other.startup_rotate;
  if ( this->size_limit==-1 )     this->size_limit = other.size_limit;
  if ( this->time_limit==-1 )     this->time_limit = other.time_limit;
  if ( this->rotation==-1 )       this->rotation = other.rotation;

  if ( this->rotation_header==-1 ) this->rotation_header = other.rotation_header;
  if ( this->rotation_footer==-1 ) this->rotation_footer = other.rotation_footer;
  if ( this->unixtime_suffix==-1 ) this->unixtime_suffix = other.unixtime_suffix;
}

void file_writer_options::finalize()
{
  if ( this->path=="#" ) this->path.clear();
  if ( this->sync==-1 ) this->sync = 1;
  if ( this->startup_rotate==-1 ) this->startup_rotate = 0;
  if ( this->size_limit==-1 )     this->size_limit = 0;
  if ( this->time_limit==-1 )     this->time_limit = 0;
  if ( this->rotation==-1 )       this->rotation = 0;
  if ( this->rotation_header==-1 ) this->rotation_header = 1;
  if ( this->rotation_footer==-1 ) this->rotation_footer = 1;
  if ( this->unixtime_suffix==-1 ) this->unixtime_suffix = 0;
}


}
