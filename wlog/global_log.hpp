//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logstream.hpp>
#include <wlog/logger_fun.hpp>
#include <string>

namespace wlog{
  
void init_log(const logger_fun& writer);
bool log_status();
logstream global_log(const std::string& name, const std::string& type);

}
