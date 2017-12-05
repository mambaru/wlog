//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "syslog_writer.hpp"
#include <syslog.h>
#include <sstream>


namespace wlog{

namespace
{
  size_t ident2pri(const std::string& ident)
  {
    if (ident=="ERROR")    return LOG_ERR;
    if (ident=="WARNING")  return LOG_WARNING;
    if (ident=="MESSAGE")  return LOG_NOTICE;
    if (ident=="FATAL")    return LOG_ALERT;
    if (ident=="BEGIN")    return LOG_INFO;
    if (ident=="END")      return LOG_INFO;
    if (ident=="DEBUG")    return LOG_DEBUG;
    if (ident=="TRACE")    return LOG_DEBUG;
    if (ident=="PROGRESS") return LOG_INFO;
    return LOG_ERR;
  }
}
  
syslog_writer::syslog_writer(const std::string& sysname)
  : _sysname(sysname)
{
}

void syslog_writer::operator()(     
    const formatter_fun& fmt,
    const char* name, 
    const char* ident,
    const std::string& str
)
{
  std::stringstream ss;
  if ( !fmt )
    fmt( ss, name, ident, str );
  else 
    ss << str;
  
  ::openlog( _sysname.c_str(), 0, LOG_USER);
  ::syslog( ident2pri(ident), "%s", ss.str().c_str() );
  ::closelog();
}

}
