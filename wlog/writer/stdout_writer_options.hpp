//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>

namespace wlog{

struct stdout_writer_options
{
  std::string name;
  int sync = -1;
};

inline stdout_writer_options& operator <<= (stdout_writer_options& self, const stdout_writer_options& other)
{
  if ( self.name.empty() ) self.name = other.name;
  if ( self.name=="#" ) self.name.clear();
  if ( self.sync==-1 ) self.sync = other.sync;
  return self;
}

}
