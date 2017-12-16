//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logger/basic_logger_options.hpp>
#include <vector>

namespace wlog{
  
struct custom_logger_options: basic_logger_options
{
  std::vector<std::string> names;
  void upgrade(const basic_logger_options& other);
  void finalize();
};

}
