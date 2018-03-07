//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logger/logger_options.hpp>
#include <string>

namespace wlog{
  
bool load(const std::string& src, logger_options* opt, std::string* err = nullptr);

logger_options load(const std::string& src, std::string* err = nullptr); 

std::string dump(const logger_options& opt);

}
