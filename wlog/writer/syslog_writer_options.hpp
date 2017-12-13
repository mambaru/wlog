//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>

namespace wlog{

struct syslog_writer_options
{
  std::string name;
};

inline syslog_writer_options& operator <<= (syslog_writer_options& self, const syslog_writer_options& other)
{
  if ( self.name.empty() ) self.name = other.name;
  if ( self.name=="#" ) self.name.clear();
  return self;
}



}
