//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "formatter.hpp"
#include <iomanip>
#include <iostream>

namespace wlog
{
  
bool formatter::set_color(std::ostream& os, const std::string& name, const std::string& color, const formatter_options& opt)
{
  auto itr = opt.color_map.find(name);
  if ( itr!=opt.color_map.end() )
  {
    os << itr->second;
    return true;
  }
  else if ( !color.empty() )
  {
    os << color;
    return true;
  }
  return false;
}

void formatter::reset_color(std::ostream& os, const std::string& name, const formatter_options& opt)
{
  auto itr = opt.color_map.find(name);
  if ( itr!=opt.color_map.end() )
  {
    os << "\033[0m";
  }
}

void formatter::reset_color(std::ostream& os)
{
  os << "\033[0m";
}


bool formatter::date( std::ostream& os, const time_point& tp, const formatter_options& opt)
{
  if ( opt.hide & hide_flags::date )
    return false;
  
  const char* old_locale=0; 
  if ( !opt.locale.empty() )
  {
    old_locale = std::setlocale(LC_TIME, nullptr);
    std::setlocale(LC_TIME, opt.locale.c_str() );
  }
  
  bool flag = false;
  if ( opt.colorized & colorized_flags::date )
    formatter::set_color(os, "$date", "\033[32m", opt);

  time_t ts = time_point::clock::to_time_t(tp);
  struct tm t1;
  localtime_r(&ts, &t1);
  char buf[100]={0};
  size_t pos=0;
  bool fulldate = opt.resolution >= resolutions::days;
  fulldate &= !(opt.hide & (hide_flags::year | hide_flags::month | hide_flags::days 
                         | hide_flags::hours | hide_flags::minutes | hide_flags::seconds) );
  
  if ( fulldate )
  {
    flag = true;
    if ( opt.locale.empty() || opt.resolution < resolutions::seconds )
    {
      //F (C++11)	equivalent to "%Y-%m-%d" (the ISO 8601 date format)
      //os << std::put_time(&t1, "%F");
      pos = strftime(buf, 100, "%F", &t1);
    }
    else
    {
      // c	writes standard date and time string, e.g. Sun Oct 17 04:41:13 2010 (locale dependent)
      //os << std::put_time(&t1, "%c");
      pos = strftime(buf, 100, "%c", &t1);
    }
  }
  else
  {
    if ( !(opt.hide & hide_flags::year ) && (opt.resolution >= resolutions::year) )
    {
      flag = true;
      // Y	writes year as a decimal number, e.g. 2017	
      //os << std::put_time(&t1, "%Y");
      pos = strftime(buf, 100, "%Y", &t1);
    }

    if ( !(opt.hide & hide_flags::month ) && (opt.resolution >= resolutions::month) )
    {
      if (flag)
        pos += strftime(buf + pos, 100-pos, " %b", &t1);
      else
        pos += strftime(buf + pos, 100-pos, "%b", &t1);
      //if (flag) os << " ";
      // b writes abbreviated month name, e.g. Oct (locale dependent)
      //os << std::put_time(&t1, "%b");
      flag = true;
    }

    if ( !(opt.hide & hide_flags::days ) && (opt.resolution >= resolutions::days) )
    {
      if (flag)
        pos += strftime(buf + pos, 100-pos, " %d %a", &t1);
      else
        pos += strftime(buf + pos, 100-pos, "%d %a", &t1);
      //if (flag) os << " ";
      // d writes day of the month as a decimal number (range [01,31])
      // a writes abbreviated weekday name, e.g. Fri (locale dependent)
      //os << std::put_time(&t1, "%d %a");
      flag = true;
    }
  }
  
  if ( pos != 0)
    os << buf;
  
  if ( opt.colorized & colorized_flags::date )
    formatter::reset_color(os);
    
  if ( !opt.locale.empty() )
  {
    
    if ( old_locale!=0 )
    {
      std::cout << "reold: " << old_locale << std::endl;
      std::setlocale(LC_TIME, old_locale );
    }
    else
    {
      std::cout << "reold: " << "EMPTY" << std::endl;
    }
  }

  /*if ( !opt.locale.empty() )
    os.imbue(old_locale);*/

  return flag;
}


bool formatter::time( std::ostream& os, const time_point& tp, const formatter_options& opt)
{
  if ( opt.hide & hide_flags::time )
    return false;

  const char* old_locale=0; 
  if ( !opt.locale.empty() )
  {
    old_locale = std::setlocale(LC_TIME, nullptr);
    std::setlocale(LC_TIME, opt.locale.c_str() );
  }
  
  if ( opt.colorized & colorized_flags::time )
    formatter::set_color(os, "$time", "\033[92m", opt);

  time_t ts = time_point::clock::to_time_t(tp);
  struct tm t1;
  localtime_r(&ts, &t1);
  char buf[100]={0};
  size_t pos=0;

  bool fulldate = opt.resolution >= resolutions::seconds;
  fulldate &= !(opt.hide & (hide_flags::hours | hide_flags::minutes | hide_flags::seconds) );
  if ( fulldate )
  {
    if ( opt.locale.empty() )
    {
      // T (C++11) equivalent to "%H:%M:%S" (the ISO 8601 time format)
      pos += strftime(buf + pos, 100-pos, "%T", &t1);

    }
    else
    {
      // X writes localized time representation (locale dependent)
      pos += strftime(buf + pos, 100-pos, "%X", &t1);
    }
  }
  else
  {
    bool flag = false;
    
    if ( !(opt.hide & hide_flags::hours ) && (opt.resolution >= resolutions::hours) )
    {
      // Hour in 24h format (00-23)	
      pos = strftime(buf, 100, "%H", &t1);
      flag = true;
    }
    
    if ( !(opt.hide & hide_flags::minutes ) && (opt.resolution >= resolutions::minutes) )
    {
      // Minute (00-59)	
      if ( flag )
        pos = strftime(buf, 100, ":%M", &t1);
      else
        pos = strftime(buf, 100, "%M", &t1);
      flag = true;
    }
    
    if ( !(opt.hide & hide_flags::seconds ) && (opt.resolution >= resolutions::seconds) )
    {
      // Second (00-61)	
      if ( flag )
        pos = strftime(buf, 100, ":%S", &t1);
      else
        pos = strftime(buf, 100, "%S", &t1);
      flag = true;
    }
  }
  
  if ( pos != 0)
    os << buf;

  if ( opt.colorized & colorized_flags::time )
    formatter::reset_color(os);

  if ( !opt.locale.empty() )
    std::setlocale(LC_TIME, old_locale );
  
  return true;
}

template<typename Ratio>
void formatter::fraction_t(std::ostream& os, const time_point& tp)
{
  auto d = tp.time_since_epoch();
  auto ts = std::chrono::duration_cast< std::chrono::duration<long, Ratio>  >(d).count();
  auto tsr = (ts/Ratio::den) * Ratio::den;
  int w = 0;
  for ( long R = Ratio::den; R!=0; R/=10, ++w );
  os << std::setfill('0') << std::setw(w-1)<< ts - tsr;
}


bool formatter::fraction( std::ostream& os, const time_point& tp, const formatter_options& opt)
{
  if ( opt.hide & hide_flags::fraction || opt.resolution <= resolutions::seconds)
    return false;
  
  if ( opt.colorized & colorized_flags::fraction )
    formatter::set_color(os, "$fraction", "\033[32m", opt);

  if ( opt.resolution == resolutions::nanoseconds )
    fraction_t<std::nano>(os, tp);
  else if ( opt.resolution == resolutions::microseconds )
    fraction_t<std::micro>(os, tp);
  else if ( opt.resolution == resolutions::milliseconds )
    fraction_t<std::milli>(os, tp);
  else if ( opt.resolution == resolutions::centiseconds )
    fraction_t<std::centi>(os, tp);
  else if ( opt.resolution == resolutions::deciseconds )
    fraction_t<std::deci>(os, tp);

  if ( opt.colorized & colorized_flags::fraction )
    formatter::reset_color(os);
  return true;
}


bool formatter::name( std::ostream& os, const std::string& name, const formatter_options& opt)
{
  if ( opt.hide & hide_flags::name)
    return false;
  
  if ( opt.colorized & colorized_flags::name )
  {
    if ( !formatter::set_color(os, name, "", opt) )
      formatter::set_color(os, "$name", "\033[94m", opt);
  }
  
  os << name;

  if ( opt.colorized & colorized_flags::name )
  {
    if ( !( opt.colorized & colorized_flags::message) 
      || !( opt.colorized & colorized_flags::message)
    )
    {
      formatter::reset_color(os);
    }
  }
  return true;
}


bool formatter::ident( std::ostream& os, const std::string& ident, const formatter_options& opt)
{
  if ( opt.hide & hide_flags::ident )
    return false;
  
  if ( opt.colorized & (colorized_flags::ident | colorized_flags::ident_ex) )
  {
    if ( !formatter::set_color(os, ident, "", opt) )
    {
      std::string color;
      if ( ident=="WARNING" )
        color = "\033[93m" ;
      else if ( ident=="ERROR")
        color = "\033[91m" ;
      else if ( ident=="FATAL" || ident=="EMERG" || ident=="CRIT" || ident=="ALERT" )
        color = "\033[31m" ;
      else if ( opt.colorized & colorized_flags::ident_ex )
      {
        if ( ident=="MESSAGE" || ident=="INFO")
          color = "\033[97m" ;
        else if ( ident=="TRACE")
          color = "\033[90m" ;
        else if ( ident=="DEBUG")
          color = "\033[33m" ;
        else if ( ident=="BEGIN" || ident=="END" || ident=="PROGRESS")
          color = "\033[96m" ;
      }
      if ( color.empty() )
        formatter::set_color(os, "$ident", "\033[94m", opt);
    }
  }
  else if ( opt.colorized!=colorized_flags::none )
  {
    formatter::reset_color(os);
  }
  
  os << ident;

  if ( opt.colorized & (colorized_flags::ident | colorized_flags::ident_ex) )
  {
    if ( !( opt.colorized & colorized_flags::message) )
    {
      formatter::reset_color(os);
    }
  }
  return true;
}

bool formatter::message( std::ostream& os, const std::string& txt, const formatter_options& opt)
{
  if ( opt.hide & hide_flags::message )
    return false;

  if ( opt.colorized & colorized_flags::message )
  {
    formatter::set_color(os, "$message", "", opt);
  }
  else if ( opt.colorized!=colorized_flags::message )
  {
    formatter::reset_color(os);
  }
  
  os << txt;
  
  if ( opt.colorized & colorized_flags::message )
    formatter::reset_color(os);

  return true;
}


formatter::formatter(const formatter_options& opt, const formatter_handlers& handlers)
  : _opt(opt)
  , _handlers(handlers)
{
  
}

void formatter::operator()(std::ostream& os, const time_point& tp, 
                           const std::string& log_name, const std::string& log_ident, const std::string& str) const
{
  if ( !_opt.locale.empty() )
    os.imbue(std::locale(_opt.locale.c_str()));

  
  if ( ( (_handlers.date != nullptr) && _handlers.date( os, tp, _opt) ) || formatter::date(os, tp, _opt) )
    os << " ";
   
  // TODO: если устаовлена только локаль, то time не вызываем 
  bool showtime = _handlers.date != nullptr;
  showtime |= _opt.resolution < resolutions::seconds;
  showtime |= _opt.hide & (hide_flags::year | hide_flags::month | hide_flags::days);
  showtime |= _opt.locale.empty();

  
  if ( ( (_handlers.time != nullptr) && _handlers.time( os, tp, _opt) ) || formatter::time(os, tp, _opt) )
  {
    if ( _handlers.fraction != nullptr )
      _handlers.fraction( os, tp, _opt);
    else
      formatter::fraction(os, tp, _opt);
  }

  if ( ( (_handlers.name != nullptr) && _handlers.name( os, log_name, _opt) ) || formatter::name(os, log_name, _opt) )
     os << " ";

  if ( ( (_handlers.ident != nullptr) && _handlers.ident( os, log_ident, _opt) ) || formatter::ident(os, log_ident, _opt) )
     os << " ";

  if ( _handlers.message != nullptr )
    _handlers.message( os, str, _opt);
  else
    formatter::message(os, str, _opt);
}

  
}
