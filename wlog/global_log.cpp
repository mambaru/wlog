//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "global_log.hpp"
#include "logstream.hpp"
#include "logger_fun.hpp"
#include <iostream>
#include <mutex>

namespace wlog{

typedef std::mutex mutex_type;
extern mutex_type log_mutex;
extern logger_fun global_writer;

logstream global_log(const std::string& name, const std::string& ident)
{
  log_mutex.lock();
  return logstream(log_mutex, name,  ident,  global_writer);
}

stdstream global_cout()
{
  log_mutex.lock();
  return stdstream(log_mutex, std::cout);
}

stdstream global_clog()
{
  log_mutex.lock();
  return stdstream(log_mutex, std::clog);
}

stdstream global_cerr()
{
  log_mutex.lock();
  return stdstream(log_mutex, std::clog);
}

}
