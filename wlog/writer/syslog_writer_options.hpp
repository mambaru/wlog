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
  syslog_writer_options& operator <<= (const syslog_writer_options& other);
};

}
