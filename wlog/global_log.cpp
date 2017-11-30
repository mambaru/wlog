//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//


#include "global_log.hpp"
#include "default_logger.hpp"
#include <mutex>

namespace wlog{

typedef std::mutex mutex_type;
mutex_type log_mutex;

static logger_fun global_writer = nullptr;

void init_log(const logger_fun& log)
{
  std::lock_guard<mutex_type> lk(log_mutex);
  global_writer = log;
}

void init_log(const options& opt)
{
  std::lock_guard<mutex_type> lk(log_mutex);
  global_writer = default_logger(opt);
}

void init_log(const std::string& path, const std::string& stdout, bool milliseconds)
{
  std::lock_guard<mutex_type> lk(log_mutex);
  options opt;
  opt.path = path;
  opt.stdout = stdout;
  opt.milliseconds = milliseconds;
  global_writer = default_logger(opt);
}


bool log_status()
{
  std::lock_guard<mutex_type> lk(log_mutex);
  return global_writer!=nullptr;
}
  
logstream global_log(const std::string& name, const std::string& type)
{
  std::lock_guard<mutex_type> lk(log_mutex);
  return logstream( name,  type,  global_writer);
}

}
