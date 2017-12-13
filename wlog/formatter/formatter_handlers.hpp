//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/types.hpp>
#include <functional>
#include <ostream>

namespace wlog{
  
struct formatter_handlers
{
  typedef std::function<bool( std::ostream&, const time_point&, const formatter_options&) >  date_fun_t;
  typedef std::function<bool( std::ostream&, const std::string&, const formatter_options&) > str_fun_t;
  
  date_fun_t date;
  date_fun_t time;
  date_fun_t fraction;
  
  str_fun_t name;
  str_fun_t ident;
  str_fun_t message;
};

inline formatter_handlers& operator <<= (formatter_handlers& self, const formatter_handlers& other)
{
  if ( self.date==nullptr )
    self.date = other.date;

  if ( self.time==nullptr )
    self.time = other.time;

  if ( self.fraction==nullptr )
    self.fraction = other.fraction;
  
  if ( self.name==nullptr )
    self.name = other.name;

  if ( self.ident==nullptr )
    self.ident = other.ident;

  if ( self.message==nullptr )
    self.message = other.message;
  
  return self;
}

}
