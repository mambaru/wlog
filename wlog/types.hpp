//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <chrono>
#include <mutex>

namespace wlog{

  typedef std::recursive_mutex mutex_type;
  using time_point = std::chrono::system_clock::time_point;
  
}
