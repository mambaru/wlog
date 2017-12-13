//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

namespace wlog{

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

inline colorized_flags operator ^ ( colorized_flags left, colorized_flags right)
{
  if ( left == colorized_flags::inherited ) left = colorized_flags::none;
  if ( right == colorized_flags::inherited ) right = colorized_flags::none;
  return static_cast<colorized_flags>( static_cast<unsigned long>(left) 
         ^ static_cast<unsigned long>(right) );
}
inline bool operator & ( colorized_flags left, colorized_flags right)
{
  if ( left == colorized_flags::inherited ) left = colorized_flags::none;
  if ( right == colorized_flags::inherited ) right = colorized_flags::none;
  return 0 != (static_cast<unsigned long>(left) & static_cast<unsigned long>(right));
}

inline bool operator!(colorized_flags flags)
{
  return static_cast<unsigned long>(flags)==0;
}

}
