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

void init_log(colorized_flags colorized, resolutions resolution )
{
  default_logger_options opt;
  opt.stdout.name = "clog";
  opt.stdout.colorized = colorized;
  opt.stdout.resolution = resolution;
  auto plog = std::make_shared<default_logger>(opt);
  std::lock_guard<mutex_type> lk(log_mutex);
  using namespace std::placeholders;
  global_writer = std::bind(&default_logger::operator(), plog, _1, _2, _3, _4);
}

void init_log(const logger_fun& log)
{
  std::lock_guard<mutex_type> lk(log_mutex);
  global_writer = log;
}

void init_log(const default_logger_options& opt)
{
  auto plog = std::make_shared<default_logger>(opt);
  std::lock_guard<mutex_type> lk(log_mutex);
  using namespace std::placeholders;
  global_writer = std::bind(&default_logger::operator(), plog, _1, _2, _3, _4);
}

void init_log(const std::string& path, resolutions resolution, const std::string& stdout, colorized_flags colorized)
{
  default_logger_options opt;
  opt.path = path;
  opt.resolution = resolution;
  opt.stdout.resolution = resolution;
  opt.stdout.name = stdout;
  opt.stdout.colorized = colorized;
  auto plog = std::make_shared<default_logger>(opt);
  std::lock_guard<mutex_type> lk(log_mutex);
  using namespace std::placeholders;
  global_writer = std::bind(&default_logger::operator(), plog, _1, _2, _3, _4);
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
