//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//


#include "init_log.hpp"
#include "logger/default_logger.hpp"
#include <iostream>
#include <mutex>

namespace wlog{

typedef std::mutex mutex_type;
extern mutex_type log_mutex;
extern logger_fun global_writer;

logger_fun&& release_log()
{
  std::lock_guard<mutex_type> lk(log_mutex);
  return std::move(global_writer);
}

void init_log(colorized_flags colorized, resolutions resolution )
{
  logger_options opt;
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

void init_log(const logger_options& opt, const logger_handlers& hdr)
{
  auto plog = std::make_shared<default_logger>(opt, hdr);
  std::lock_guard<mutex_type> lk(log_mutex);
  using namespace std::placeholders;
  global_writer = std::bind(&default_logger::operator(), plog, _1, _2, _3, _4);
}

void init_log(const std::string& path, resolutions resolution, const std::string& stdout, colorized_flags colorized)
{
  logger_options opt;
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
  
}
