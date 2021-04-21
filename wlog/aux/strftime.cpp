#include <time.h>
#include "strftime.hpp"

namespace wlog
{
  
size_t strftime(char *s, size_t max, const char *fmt,
            const tm *tm)
{
  if ( s == nullptr )
    return 0;
  return ::strftime(s, max, fmt, tm);
}

}
