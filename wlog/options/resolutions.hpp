//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

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
  year         = -6
};
  
}
