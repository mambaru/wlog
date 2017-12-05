//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "formatter.hpp"
#include <iomanip>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <iostream>

namespace wlog{
  
namespace{

  std::string mkms()
  {
    auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    auto secround = (millis/1000) * 1000;
    std::stringstream ss;
    ss <<std::setfill('0') << std::setw(3)<< millis - secround;
    return ss.str();
  }

  std::string mktime(time_t ts)
  {
    struct tm t1;
    localtime_r(&ts, &t1);
    char buf[100];
    int sz = strftime(buf,sizeof(buf), "%H:%M:%S",&t1);
    return std::string(buf, static_cast<std::string::size_type>(sz) );
  }

  std::string mkdate(time_t ts)
  {
    struct tm t1;
    localtime_r(&ts, &t1);
    char buf[100];
    int sz = strftime(buf,sizeof(buf), "%Y-%m-%d",&t1);
    return std::string(buf, static_cast<std::string::size_type>(sz) );
  }
}
  
file_formatter::file_formatter(bool milliseconds)
  : _milliseconds(milliseconds)
{
}

void file_formatter::operator()(
    std::ostream& os, 
    const char* name, 
    const char* ident,
    const std::string& str
  ) const
{
  time_t ts = time(0);
  os << mkdate(ts) << " " << mktime(ts);
  if ( _milliseconds )
    os << "." << mkms();
  os << " " << name << " " << ident << " " << str;
}

stdout_formatter::stdout_formatter(bool milliseconds, bool colorized)
  : _milliseconds(milliseconds)
  , _colorized(colorized)
{
}

void stdout_formatter::operator()(
    std::ostream& os, 
    const char* name, 
    const char* ident,
    const std::string& str
  ) const
{
  time_t ts = time(0);
  if ( _colorized )
    os << "\033[32m" ;
  os << mkdate(ts) << " ";
  if ( _colorized )
    os << "\033[92m" ;
  os << mktime(ts);
  

  if ( _milliseconds )
  {
    if ( _colorized )
      os << "\033[32m" ;
    os << "." << mkms();
  }
  if ( _colorized )
    os << "\033[94m" ;

  os << " " << name;

  if ( _colorized )
  {
    if ( 0==strcmp(ident,"MESSAGE") )
      os << "\033[97m" ;
    else if ( 0==strcmp(ident,"WARNING"))
      os << "\033[93m" ;
    else if ( 0==strcmp(ident,"TRACE"))
      os << "\033[90m" ;
    else if ( 0==strcmp(ident,"DEBUG"))
      os << "\033[33m" ;
    else if ( 0==strcmp(ident,"ERROR"))
      os << "\033[91m" ;
    else if ( 0==strcmp(ident,"FATAL"))
      os << "\033[31m" ;
    else if ( 0==strcmp(ident,"BEGIN") || 0==strcmp(ident,"END") || 0==strcmp(ident,"PROGRESS"))
      os << "\033[96m" ;
    else
      os << "\033[0m" ;
  }

  os << " " << ident;
  os << " " << str;
  if ( _colorized )
    os << "\033[0m" ;
}

syslog_formatter::syslog_formatter()
{
}

void syslog_formatter::operator()(
    std::ostream& os, 
    const char* , 
    const char* ,
    const std::string& str
  ) const
{
  os << str;
}
  
}
