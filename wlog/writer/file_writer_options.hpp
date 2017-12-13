//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>

namespace wlog{

struct file_writer_options
{
  std::string path;
  int sync = -1;
  int startup_rotate = -1; 
  long size_limit = -1;
  long time_limit = -1;
  long rotation   = -1; // ex save old
};

inline file_writer_options& operator <<= (file_writer_options& self, const file_writer_options& other)
{
  if ( self.path.empty() ) self.path = other.path;
  if ( self.path=="#" ) self.path.clear();
  if ( self.sync==-1 ) self.sync = other.sync;
  
  if ( self.startup_rotate==-1 ) self.startup_rotate = other.startup_rotate;
  if ( self.size_limit==-1 )     self.size_limit = other.size_limit;
  if ( self.time_limit==-1 )     self.time_limit = other.time_limit;
  if ( self.rotation==-1 )       self.rotation = other.rotation;
  return self;
}

}
