//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/formatter/formatter_options.hpp>
#include <wlog/types.hpp>
#include <functional>
#include <ostream>

namespace wlog{
  
struct formatter_handlers
{
  typedef std::function<std::string(const time_point&) >  date_fun_t;
  typedef std::function<std::string(const std::string&) > str_fun_t;
  
  date_fun_t date;
  date_fun_t time;
  date_fun_t fraction;
  
  str_fun_t name;
  str_fun_t ident;
  str_fun_t message;
  
  void upgrade (const formatter_handlers& other);
};



}
