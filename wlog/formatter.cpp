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
#include <ctime>

namespace wlog{

/*  
namespace{

  std::string mkms()
  {
    auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    auto secround = (millis/1000) * 1000;
    std::stringstream ss;
    ss <<std::setfill('0') << std::setw(3)<< millis - secround ;
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
*/
  
void formatter::date(std::ostream& os, const time_point& tp, unsigned long hide)
{
  if ( hide & ulong(hide_items::date) )
    return;
    
  time_t ts = time_point::clock::to_time_t(tp);
  struct tm t1;
  localtime_r(&ts, &t1);
  
  bool flag = false;
  if ( !(hide & ulong(hide_items::year) ) )
  {
    flag = true;
    os << std::setfill('0') << std::setw(2)
       << int(t1.tm_year) + 1900;
  }
  
  if ( !( hide & long(hide_items::month) ) )
  {
    if (flag) os << "-";
    flag = true;
    os << std::setfill('0') << std::setw(2)
       << t1.tm_mon;
  }

  if ( !( hide & long(hide_items::day) ) )
  {
    if (flag) os << "-";
    flag = true;
    os << std::setfill('0') << std::setw(2)
       << t1.tm_mday;
  }
  
  if (flag)
    os << " ";
  /*
  char buf[100];
  int sz = strftime(buf,sizeof(buf), "%Y-%m-%d",&t1);
  os << std::string(buf, static_cast<std::string::size_type>(sz) );
  */
}

void formatter::time(std::ostream& os,const time_point& tp, unsigned long hide)
{
  if ( hide & ulong(hide_items::time) )
    return;

  time_t ts = time_point::clock::to_time_t(tp);
  struct tm t1;
  localtime_r(&ts, &t1);

  bool flag = false;
  if ( !(hide & ulong(hide_items::hour) ) )
  {
    flag = true;
    os << std::setfill('0') << std::setw(2)
       << t1.tm_hour;
  }
  
  if ( !( hide & long(hide_items::minute) ) )
  {
    if (flag) os << ":";
    flag = true;
    os << std::setfill('0') << std::setw(2)
       << t1.tm_min;
  }

  if ( !( hide & long(hide_items::second) ) )
  {
    if (flag) os << ":";
    flag = true;
    os << std::setfill('0') << std::setw(2)
       << t1.tm_sec;
  }
  
  if (flag)
    os << " ";
  
  /*
  char buf[100];
  int sz = strftime(buf,sizeof(buf), "%H:%M:%S",&t1);
  os << std::string(buf, static_cast<std::string::size_type>(sz) );
  */
}

namespace{
  
template<typename Ratio>
void msx(std::ostream& os, const time_point& tp)
{
  auto d = tp.time_since_epoch();
  auto ts = std::chrono::duration_cast< std::chrono::duration<long, Ratio>  >(d).count();
  auto tsr = (ts/Ratio::den) * Ratio::den;
  int w = 0;
  for ( long R = Ratio::den; R!=0; R/=10, ++w );
  os <<std::setfill('0') << std::setw(w-1)<< ts - tsr;
}

}


void formatter::ms(std::ostream& os, const time_point& tp, long resolution)
{
  if ( resolution >= std::nano::den )
    msx<std::nano>(os, tp);
  else if ( resolution >= std::micro::den )
    msx<std::micro>(os, tp);
  else if ( resolution >= std::milli::den )
    msx<std::milli>(os, tp);
  else if ( resolution >= std::centi::den )
    msx<std::centi>(os, tp);
  else if ( resolution >= std::deci::den )
    msx<std::deci>(os, tp);
  
/*
  auto duration = tp.time_since_epoch();
  size_t ts = 0;
  size_t tsr = 0;
  if ( resolution >= 1000000000 )
  {
    ts = std::chrono::duration_cast< std::chrono::duration<long, std::deci>  >(duration).count();
    tsr = (ts/1000000000) * 1000000000;
  }
  auto secround = (millis/10) * 10;
  os <<std::setfill('0') << std::setw(1)<< millis - secround ;
  */
}

file_formatter::file_formatter(resolutions resolution, datetime_formatter_fun date_fmt, datetime_formatter_fun time_fmt)
  : _resolution(resolution)
  , _date_fmt(date_fmt)
  , _time_fmt(time_fmt)

{
}

void file_formatter::operator()(
    std::ostream& os, 
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  ) const
{
  /*time_t ts = time(0);
  os << mkdate(ts) << " " << mktime(ts);
  */
  formatter::date(os, tp, 0ul );
  formatter::time(os, tp, 0ul);

  if ( _resolution != resolutions::seconds )
  {
    formatter::ms(os, tp, static_cast<long>(_resolution) );
  }
    //os << "." << mkms();
  os << " " << name << " " << ident << " " << str;
}

stdout_formatter::stdout_formatter(resolutions resolution, long colorized, ulong hide)
  : _resolution(resolution != resolutions::inherited ? resolution : resolutions::milliseconds )
  , _colorized(colorized > 0 ? colorized : 3)
  , _hide( hide != ulong(hide_items::inherited) ? hide : 0ul )
{
}

void stdout_formatter::operator()(
    std::ostream& os, 
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  ) const
{
  
  //time_t ts = time(0);
  if ( _colorized > 2 )
    os << "\033[32m" ;
  
  formatter::date(os, tp, 0ul);
  if ( _colorized > 2 )
    os << "\033[92m" ;
  formatter::time(os, tp, 0ul);

  if ( _resolution != resolutions::seconds &&
    !( _hide & ulong(hide_items::time))
  )
  {
    if ( _colorized > 2 )
      os << "\033[32m" ;
    os << ".";
    formatter::ms(os, tp, static_cast<long>(_resolution) );
    //os << "." << mkms();
  }
  if ( _colorized > 2 )
    os << "\033[94m" ;

  os << " " << name;

  if ( _colorized > 0 )
  {
    if ( ident=="WARNING" )
      os << "\033[93m" ;
    else if ( ident=="ERROR")
      os << "\033[91m" ;
    else if ( ident=="FATAL" || ident=="EMERG" || ident=="CRIT" || ident=="ALERT" )
      os << "\033[31m" ;
    else if ( _colorized > 1 )
    {
      if ( ident=="MESSAGE" || ident=="INFO")
        os << "\033[97m" ;
      else if ( ident=="TRACE")
        os << "\033[90m" ;
      else if ( ident=="DEBUG")
        os << "\033[33m" ;
      else if ( ident=="BEGIN" || ident=="END" || ident=="PROGRESS")
        os << "\033[96m" ;
      else
        os << "\033[0m" ;
    }
    else
      os << "\033[0m" ;
      
  }

  os << " " << ident;
  os << " " << str;
  if ( _colorized > 0 )
    os << "\033[0m" ;
}

syslog_formatter::syslog_formatter()
{
}

void syslog_formatter::operator()(
    std::ostream& os, 
    const time_point& ,
    const std::string& , 
    const std::string& ,
    const std::string& str
  ) const
{
  os << str;
}
  
}
