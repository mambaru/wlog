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
  
void init_log(const std::string& stdout = "clog", resolutions resolution = resolutions::milliseconds, long colorized = 3);
void init_log(const logger_fun& log);
void init_log(const options& opt);
void init_log(const std::string& path, resolutions resolution = resolutions::milliseconds, const std::string& stdout = "clog", long colorized = 3);

// @return текущий логгер. М.б. использован для записи финального сообщения
logger_fun&& release_log();
bool log_status();

logstream global_log(const std::string& name, const std::string& ident);

}
