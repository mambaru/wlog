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

void disable();

void init(const logger_fun& log);

void init(
  const logger_options& opt, 
  const logger_handlers& hdr=logger_handlers()
);

void init(
  resolutions resolution = resolutions::seconds,
  colorized_flags colorized = full_color
);

void init(
  const std::string& path, 
  resolutions resolution = resolutions::seconds, 
  colorized_flags colorized = full_color);

// @return текущий логгер. М.б. использован для записи финального сообщения
logger_fun&& release();

bool status();

}
