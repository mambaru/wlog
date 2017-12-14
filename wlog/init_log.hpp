//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logger/logger_options.hpp>
#include <wlog/logger/logger_handlers.hpp>
#include <wlog/logger_fun.hpp>
#include <string>

namespace wlog{

void init_log(const logger_fun& log);

void init_log(
  const logger_options& opt, 
  const logger_handlers& hdr=logger_handlers()
);

void init_log(
  colorized_flags colorized = full_color,
  resolutions resolution = resolutions::milliseconds
);

void init_log(
  const std::string& path, 
  resolutions resolution = resolutions::milliseconds, 
  const std::string& stdout = "clog", 
  colorized_flags colorized = full_color);

// @return текущий логгер. М.б. использован для записи финального сообщения
logger_fun&& release_log();

bool log_status();

}
