//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/options/basic_logger_handlers.hpp>
#include <map>
#include <string>

namespace wlog{
  
struct logger_handlers: basic_logger_handlers
{
 typedef std::map<std::string, basic_logger_handlers> customize_map;
 customize_map customize;

  void upgrade()
  {
    for (auto& op : customize)
      op.second <<= static_cast< const basic_logger_handlers&>(*this);
  }
};

}
