//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//


#include "global_log.hpp"

namespace wlog{

static logger_fun global_writer = nullptr;

void init_log(const logger_fun& writer)
{
  global_writer = writer;
}

bool log_status()
{
  return global_writer!=nullptr;
}
  
logstream global_log(const std::string& name, const std::string& type)
{
  return logstream( name,  type,  global_writer);
}

}
