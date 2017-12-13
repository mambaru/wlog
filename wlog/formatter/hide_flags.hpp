//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

namespace wlog{
  
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

inline hide_flags operator ^ ( hide_flags left, hide_flags right)
{
  if ( left == hide_flags::inherited ) left = hide_flags::none;
  if ( right == hide_flags::inherited ) right = hide_flags::none;
  return static_cast<hide_flags>( static_cast<unsigned long>(left) 
         ^ static_cast<unsigned long>(right) );
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


}
