//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logstream.hpp>
#include <wlog/options.hpp>
#include <wlog/logger_fun.hpp>
#include <string>

namespace wlog{

void init_log(const logger_fun& log);

void init_log(const default_logger_options& opt, const default_logger_handlers& hdr=default_logger_handlers());

void init_log(
  colorized_flags colorized = colorized_flags::all,
  resolutions resolution = resolutions::milliseconds
);

void init_log(
  const std::string& path, 
  resolutions resolution = resolutions::milliseconds, 
  const std::string& stdout = "clog", 
  colorized_flags colorized = colorized_flags::all);

// @return текущий логгер. М.б. использован для записи финального сообщения
logger_fun&& release_log();
bool log_status();

logstream global_log(const std::string& name, const std::string& ident);
stdout_stream global_cout();
stdout_stream global_clog();
stdout_stream global_cerr();

}
