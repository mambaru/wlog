//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once
#include <time.h>

namespace wlog
{
  
size_t strftime(char *s, size_t max, const char *fmt,
            const struct tm *tm);

}
