#include <time.h>
#include "strftime.hpp"

#pragma GCC diagnostic ignored "-Wformat-nonliteral"
namespace wlog
{
  
size_t strftime(char *s, size_t max, const char *fmt,
            const struct tm *tm)
{
    return ::strftime(s, max, fmt, tm);
}

}
