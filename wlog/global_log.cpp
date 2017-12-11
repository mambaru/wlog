//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//


#include "global_log.hpp"
#include "default_logger.hpp"
#include <iostream>
#include <mutex>

namespace wlog{

typedef std::mutex mutex_type;
mutex_type log_mutex;

static logger_fun global_writer = nullptr;

logger_fun&& release_log()
{
  std::lock_guard<mutex_type> lk(log_mutex);
  return std::move(global_writer);
}

void init_log(const std::string& stdout, resolutions resolution, colorized_flags colorized )
{
  default_logger_options opt;
  opt.stdout.name = stdout;
  opt.resolution = resolution;
  opt.colorized = colorized;
  std::lock_guard<mutex_type> lk(log_mutex);
  /*!!! global_writer = default_logger( opt );*/
}

void init_log(const logger_fun& log)
{
  std::lock_guard<mutex_type> lk(log_mutex);
  global_writer = log;
}

void init_log(const default_logger_options& /*opt*/)
{
  std::lock_guard<mutex_type> lk(log_mutex);
  /*!!! global_writer = default_logger(opt);*/
}

void init_log(const std::string& path, resolutions resolution, const std::string& stdout, colorized_flags colorized)
{
  default_logger_options opt;
  opt.path = path;
  opt.stdout.name = stdout;
  opt.colorized = colorized;
  opt.resolution = resolution;
  std::lock_guard<mutex_type> lk(log_mutex);
  /*!!! global_writer = default_logger(opt); */
}


bool log_status()
{
  std::lock_guard<mutex_type> lk(log_mutex);
  return global_writer!=nullptr;
}
  
logstream global_log(const std::string& name, const std::string& ident)
{
  log_mutex.lock();
  return logstream(log_mutex, name,  ident,  global_writer);
}

stdout_stream global_cout()
{
  log_mutex.lock();
  return stdout_stream(log_mutex, std::cout);
}

stdout_stream global_clog()
{
  log_mutex.lock();
  return stdout_stream(log_mutex, std::clog);
}

stdout_stream global_cerr()
{
  log_mutex.lock();
  return stdout_stream(log_mutex, std::clog);
}

}
