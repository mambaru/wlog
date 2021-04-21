//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

namespace wlog{

enum class colorized_flags: unsigned short
{
  none          = 0,
  date          = 1,
  time          = 1 << 1,
  fraction      = 1 << 2,
  name          = 1 << 3,
  notice        = 1 << 4,
  ident         = 1 << 5,
  message       = 1 << 6,
  all           = 0x7F, 
  inherited     = 1 << 8,
  all4json      = 1 << 9
};

constexpr colorized_flags full_color = colorized_flags::all;
constexpr colorized_flags get_full_color() { return full_color; }

inline colorized_flags operator | ( colorized_flags left, colorized_flags right)
{
  return static_cast<colorized_flags>(static_cast<unsigned short>(left) | static_cast<unsigned short>(right) );
}

inline colorized_flags operator ^ ( colorized_flags left, colorized_flags right)
{
  return static_cast<colorized_flags>( static_cast<unsigned short>(left) ^ static_cast<unsigned short>(right) );
}

inline colorized_flags operator & ( colorized_flags left, colorized_flags right)
{
  return static_cast<colorized_flags>(static_cast<unsigned short>(left) & static_cast<unsigned short>(right) );
}

inline bool operator!(colorized_flags flags)
{
  return static_cast<unsigned short>(flags)==0;
}

}
