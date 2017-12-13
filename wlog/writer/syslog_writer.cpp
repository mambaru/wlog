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
  /*
   * 0 - Emergency. A "panic" condition affecting multiple applications, servers, or sites. System is unusable. 
   *      Notify all technical staff on call.
   * 1 - Alert. A condition requiring immediate correction, for example, the loss of a backup ISP connection. 
   *      Notify staff who can fix the problem.
   * 2 - Critical. A condition requiring immediate correction or indicating a failure in a primary system, for example, 
   *      a loss of a primary ISP connection. Fix CRITICAL issues before ALERT-level problems.
   * 3 - Error. Non-urgent failures. Notify developers or administrators as errors must be resolved within a given time.
   * 4 - Warning. Warning messages are not errors, but they indicate that an error will occur if required action is not taken. 
   *      An example is a file system that is 85% full. Each item must be resolved within a given time.
   * 5 - Notice. Events that are unusual but are not error conditions. These items might be summarized in an email 
   *      to developers or administrators to spot potential problems. No immediate action is required.
   * 6 - Informational. Normal operational messages. These may be harvested for network maintenance functions like 
   *      reporting and throughput measurement. No action is required.
   * 7 - Debug. Information useful to developers for debugging an application. This information is not useful during operations.
   */
  size_t ident2pri(const std::string& ident)
  {
    if (ident=="EMERG")    return LOG_EMERG;
    if (ident=="ALERT")    return LOG_ALERT;
    if (ident=="CRIT")     return LOG_CRIT;
    if (ident=="NOTICE")   return LOG_NOTICE;
    if (ident=="INFO")     return LOG_INFO;
    
    if (ident=="FATAL")    return LOG_CRIT;
    if (ident=="ERROR")    return LOG_ERR;
    if (ident=="WARNING")  return LOG_WARNING;
    if (ident=="MESSAGE")  return LOG_INFO;
    
    if (ident=="BEGIN")    return LOG_INFO;
    if (ident=="END")      return LOG_INFO;
    if (ident=="PROGRESS") return LOG_INFO;
    if (ident=="DEBUG")    return LOG_DEBUG;
    if (ident=="TRACE")    return LOG_DEBUG;
    return LOG_ERR;
  }
}
  
syslog_writer::syslog_writer(const formatter_fun& formatter, const options& opt)
  : _formatter(formatter)
  , _sysname(opt.name)
{
}

void syslog_writer::operator()(     
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
)
{
  std::stringstream ss;
  if ( _formatter!=nullptr )
    _formatter( ss, tp, name, ident, str );
  else 
    ss << str;
  
  ::openlog( _sysname.c_str(), 0, LOG_USER);
  ::syslog( ident2pri(ident), "%s", ss.str().c_str() );
  ::closelog();
}

}
