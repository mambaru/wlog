//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

namespace wlog{
  
enum class resolutions: long
{
  inherited    = -1,
  nanoseconds  = 1000000000,
  microseconds = 1000000,
  milliseconds = 1000,
  centiseconds = 100,
  deciseconds  = 10,
  seconds      = 0
};

enum class hide_items: unsigned long
{
  inherited     = ~0ul,
  none          = 0x0,
  date          = 1,
  time          = 1 << 1,
  message       = 1 << 2,
  year          = 1 << 3,
  month         = 1 << 4,
  day           = 1 << 5,
  hour          = 1 << 6,
  minute        = 1 << 7,
  second        = 1 << 8
};


}
