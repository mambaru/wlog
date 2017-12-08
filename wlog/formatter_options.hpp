//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/types.hpp>
#include <functional>
#include <string>
#include <unordered_map>


namespace wlog{
  
enum class resolutions: long
{
  inherited    = 0,
  nanoseconds  = 1000000000,
  microseconds = 1000000,
  milliseconds = 1000,
  centiseconds = 100,
  deciseconds  = 10,
  seconds      = -1,
  minutes      = -2,
  hours        = -3,
  days         = -4,
  month        = -5,
  year         = -6/*,
  none         = -7*/
};


enum class hide_flags: unsigned long
{
  inherited     = ~0ul,
  none          = 0x0,
  date          = 1,
  time          = 1 << 1,
  year          = 1 << 3,
  month         = 1 << 4,
  weekday       = 1 << 5,
  days          = 1 << 6,
  hours         = 1 << 7,
  minutes       = 1 << 8,
  seconds       = 1 << 9,
  fraction      = 1 << 10,
  name          = 1 << 11,
  ident         = 1 << 12,
  message       = 1 << 13
};

inline hide_flags operator | ( hide_flags left, hide_flags right)
{
  if ( left == hide_flags::inherited ) left = hide_flags::none;
  if ( right == hide_flags::inherited ) right = hide_flags::none;
  return static_cast<hide_flags>( static_cast<unsigned long>(left) 
  | static_cast<unsigned long>(right) );
}

inline bool operator & ( hide_flags left, hide_flags right)
{
  if ( left == hide_flags::inherited ) left = hide_flags::none;
  if ( right == hide_flags::inherited ) right = hide_flags::none;
  return 0 != (static_cast<unsigned long>(left) & static_cast<unsigned long>(right));
}

inline bool operator!(hide_flags flags)
{
  return static_cast<unsigned long>(flags)==0;
}

enum class colorized_flags: unsigned long
{
  inherited     = ~0ul,
  none          = 0x0,
  date          = 1,
  time          = 1 << 1,
  fraction      = 1 << 2,
  name          = 1 << 3,
  ident         = 1 << 4,
  ident_ex      = 1 << 5,
  message       = 1 << 6,
  all           = 0xffffffff
};

inline colorized_flags operator | ( colorized_flags left, colorized_flags right)
{
  if ( left == colorized_flags::inherited ) left = colorized_flags::none;
  if ( right == colorized_flags::inherited ) right = colorized_flags::none;
  return static_cast<colorized_flags>( static_cast<unsigned long>(left) 
  | static_cast<unsigned long>(right) );
}

inline bool operator & ( colorized_flags left, colorized_flags right)
{
  if ( left == colorized_flags::inherited ) left = colorized_flags::none;
  if ( right == colorized_flags::inherited ) right = colorized_flags::none;
  return 0 != (static_cast<unsigned long>(left) & static_cast<unsigned long>(right));
}


struct formatter_options
{
  /// Включает вывод миллисекунд в поле времени лога
  resolutions resolution = resolutions::inherited;
  hide_flags hide = hide_flags::inherited;
  colorized_flags colorized = colorized_flags::inherited;
  std::string locale;
  std::unordered_map<std::string, std::string> color_map;
};

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


}
