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

formatter::formatter(const formatter_options& opt, const formatter_handlers& handlers)
  : _opt(opt)
  , _handlers(handlers)
{
  _opt.finalize();

  if ( !_opt.format.empty() )
  {
    _showtime = false;
  }
  else
  {
    _showtime = _handlers.date != nullptr;
    _showtime |= _opt.resolution < resolutions::seconds;
    _showtime |= bool( _opt.hide & (hide_flags::year | hide_flags::month | hide_flags::days) );
    _showtime |= _opt.locale.empty();
    _showfract =  !(_opt.hide & hide_flags::fraction) && _opt.resolution > resolutions::seconds;
  }
}

  
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
  if ( !!(opt.hide & hide_flags::date) )
    return false;

  char buf[256]={0};
  time_t ts = time_point::clock::to_time_t(tp);
  struct tm t1;
  localtime_r(&ts, &t1);

  /*
  if ( !opt.format.empty() )
  {
    size_t pos = strftime(buf, 100, "%F", &t1);
    return;
  }*/
  
  
  const char* old_locale=0; 
  if ( !opt.locale.empty() )
  {
    old_locale = std::setlocale(LC_TIME, nullptr);
    std::setlocale(LC_TIME, opt.locale.c_str() );
  }
  
  bool flag = false;
  if ( bool(opt.colorized & colorized_flags::date) )
    formatter::set_color(os, "$date", "\033[32m", opt);

  
  size_t pos=0;
  bool fulldate = opt.resolution >= resolutions::days;
  fulldate &= !(opt.hide & (hide_flags::year | hide_flags::month | hide_flags::days 
                         | hide_flags::hours | hide_flags::minutes | hide_flags::seconds) );
  if ( fulldate )
  {
    flag = true;
    if (!opt.format.empty() )
    {
      pos = strftime(buf, 100, opt.format.c_str(), &t1);
    }
    else if ( opt.locale.empty() || opt.resolution < resolutions::seconds )
    {
      //F (C++11)	equivalent to "%Y-%m-%d" (the ISO 8601 date format)
      pos = strftime(buf, 100, "%F", &t1);
    }
    else
    {
      // c	writes standard date and time string, e.g. Sun Oct 17 04:41:13 2010 (locale dependent)
      pos = strftime(buf, 100, "%c", &t1);
    }
  }
  else
  {
    if ( !(opt.hide & hide_flags::year ) && (opt.resolution >= resolutions::year) )
    {
      flag = true;
      // Y	writes year as a decimal number, e.g. 2017	
      pos = strftime(buf, 100, "%Y", &t1);
    }

    if ( !(opt.hide & hide_flags::month ) && (opt.resolution >= resolutions::month) )
    {
      // b writes abbreviated month name, e.g. Oct (locale dependent)
      if (flag)
        pos += strftime(buf + pos, 100-pos, " %b", &t1);
      else
        pos += strftime(buf + pos, 100-pos, "%b", &t1);
      flag = true;
    }

    if ( !(opt.hide & hide_flags::days ) && (opt.resolution >= resolutions::days) )
    {
      // d writes day of the month as a decimal number (range [01,31])
      // a writes abbreviated weekday name, e.g. Fri (locale dependent)
      if (flag) buf[pos++]=' ';
      pos += strftime(buf + pos, 100-pos, "%d", &t1);
      if ( !(opt.hide & hide_flags::weekday ) )
      pos += strftime(buf + pos, 100-pos, " %a", &t1);
      flag = true;
    }
  }
  
  if ( pos != 0)
    os << buf;
  
  if ( bool(opt.colorized & colorized_flags::date) )
    formatter::reset_color(os);
    
  if ( !opt.locale.empty() )
  {
    std::setlocale(LC_TIME, old_locale );
  }

  return flag;
}


bool formatter::time( std::ostream& os, const time_point& tp, const formatter_options& opt)
{
  if ( !!(opt.hide & hide_flags::time) )
    return false;

  const char* old_locale=0; 
  if ( !opt.locale.empty() )
  {
    old_locale = std::setlocale(LC_TIME, nullptr);
    std::setlocale(LC_TIME, opt.locale.c_str() );
  }
  
  if ( bool(opt.colorized & colorized_flags::time) )
    formatter::set_color(os, "$time", "\033[92m", opt);

  time_t ts = time_point::clock::to_time_t(tp);
  struct tm t1;
  localtime_r(&ts, &t1);
  char buf[100]={0};
  size_t pos=0;

  bool fulltime = opt.resolution >= resolutions::seconds;
  fulltime &= !(opt.hide & (hide_flags::hours | hide_flags::minutes | hide_flags::seconds) );
  if ( fulltime )
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
      pos += strftime(buf + pos, 100, "%H", &t1);
      flag = true;
    }
    
    if ( !(opt.hide & hide_flags::minutes ) && (opt.resolution >= resolutions::minutes) )
    {
      // Minute (00-59)	
      if ( flag )
        pos += strftime(buf + pos, 100, ":%M", &t1);
      else
        pos += strftime(buf + pos, 100, "%Mm ", &t1);
      flag = true;
    }
    
    if ( !(opt.hide & hide_flags::seconds ) && (opt.resolution >= resolutions::seconds) )
    {
      // Second (00-61)	
      if ( flag && !(opt.hide & hide_flags::hours ) )
        pos += strftime(buf + pos, 100, ":%S", &t1);
      else
        pos += strftime(buf + pos, 100, "%Ss", &t1);
      flag = true;
    }
  }
  
  if ( pos != 0)
    os << buf;

  if ( bool(opt.colorized & colorized_flags::time) )
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
  if ( bool(opt.hide & hide_flags::fraction) || opt.resolution <= resolutions::seconds)
    return false;
  
  if ( bool(opt.colorized & colorized_flags::fraction) )
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

  if ( bool(opt.colorized & colorized_flags::fraction) )
    formatter::reset_color(os);
  return true;
}


bool formatter::name( std::ostream& os, const std::string& name, const formatter_options& opt)
{
  if ( bool(opt.hide & hide_flags::name) )
    return false;
  
  if ( bool(opt.colorized & colorized_flags::name) )
  {
    if ( !formatter::set_color(os, name, "", opt) )
      formatter::set_color(os, "$name", "\033[36m", opt);
  }
  
  os << name;
  return true;
}


bool formatter::ident( std::ostream& os, const std::string& ident, const formatter_options& opt)
{
  bool flag = false;
  bool is_colorized = bool( opt.colorized & (colorized_flags::ident | colorized_flags::notice) );
  
  if ( is_colorized )
  {
    if ( !formatter::set_color(os, ident, "", opt) )
    {
      if ( !(opt.hide & hide_flags::ident) )
      {
        formatter::set_color(os, "$ident", "\033[0m", opt);
      }
      else
      {
        formatter::set_color(os, "$ident", "", opt);
      }
    }
  }
  else if ( opt.colorized!=colorized_flags::none )
  {
    formatter::reset_color(os);
  }
  
  if ( !(opt.hide & hide_flags::ident) )
  {
    flag = true;
    os << ident;
  }

  if ( is_colorized )
  {
    if ( !( opt.colorized & colorized_flags::message) )
    {
      formatter::reset_color(os);
    }
  }
  return flag;
}

bool formatter::message( std::ostream& os, const std::string& txt, const formatter_options& opt)
{
  if ( bool(opt.hide & hide_flags::message) )
    return false;

  if ( opt.colorized != colorized_flags::none)
  {
    if ( bool(opt.colorized & colorized_flags::message) )
    {
      formatter::set_color(os, "$message", "", opt);
    }
  }
  
  os << txt;

  if ( opt.colorized != colorized_flags::none)
  {
    formatter::reset_color(os);
  }
  return true;
}



void formatter::operator()(std::ostream& os, const time_point& tp, 
                           const std::string& log_name, const std::string& log_ident, const std::string& str) const
{
 
  if ( !_opt.locale.empty() )
    os.imbue(std::locale(_opt.locale.c_str()));

  bool flag = false;
  if ( _handlers.date != nullptr )
    flag = _handlers.date( os, tp, _opt);
  else
    flag = formatter::date(os, tp, _opt);

  if ( flag )
    os << " ";
  
  flag = false;
  if ( _showtime )
  {
    if ( _handlers.time != nullptr )
      flag = _handlers.time( os, tp, _opt);
    else
      flag = formatter::time(os, tp, _opt);
  }

  if ( _showfract )
    os << std::use_facet< std::numpunct<char> >(os.getloc()).decimal_point();;
  
  if ( ( (_handlers.fraction != nullptr) && _handlers.fraction( os, tp, _opt) ) || formatter::fraction(os, tp, _opt) )
  {
    flag = true;
  }
  
  if ( flag )
    os << " ";

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
