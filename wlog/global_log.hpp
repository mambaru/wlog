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
  
void init_log(const std::string& stdout = "clog", bool milliseconds = true, bool colorized = true);
void init_log(const logger_fun& log);
void init_log(const options& opt);
void init_log(const std::string& path, bool milliseconds = true, const std::string& stdout = "clog", bool colorized = true);
void release_log();
bool log_status();

logstream global_log(const std::string& name, const std::string& ident);

}
