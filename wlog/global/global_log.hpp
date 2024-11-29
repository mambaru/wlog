//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>
#include <wlog/global/logstream.hpp>
#include <wlog/global/stdstream.hpp>

namespace wlog{

extern mutex_type log_mutex;
extern logger_fun global_writer;

logstream global_log(const std::string& name, const std::string& ident);
stdstream global_cout();
stdstream global_clog();
stdstream global_cerr();

}
