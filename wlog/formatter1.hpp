//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>
#include <set>
#include <wlog/logger_fun.hpp>
#include <wlog/resolutions.hpp>
#include <iostream>

namespace wlog{

class formatter1
{
public:
  static void date(std::ostream& os,   const time_point& tp, unsigned long hide, long colorized);
  static void time(std::ostream& os,   const time_point& tp, unsigned long hide, long colorized);
  static void ms(std::ostream& os,     const time_point& tp, long resolution, unsigned long hide, long colorized);
  static void name(std::ostream& os,   const std::string& n, unsigned long hide, long colorized);
  static void ident(std::ostream& os,  const std::string& i, unsigned long hide, long colorized);
  
  template<typename Ratio>
  static void ms_t(std::ostream& os, const time_point& tp, long resolution);

};

class file_formatter
{
public:
  
  file_formatter(resolutions resolution, datetime_formatter_fun date_fmt = nullptr, datetime_formatter_fun time_fmt = nullptr );
  void operator()(
    std::ostream& os, 
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  ) const;
private:
  const resolutions _resolution;
  const datetime_formatter_fun _date_fmt;
  const datetime_formatter_fun _time_fmt;
};

class stdout_formatter
{
public:
  stdout_formatter(resolutions resolution, long colorized, ulong hide);
  void operator()(
    std::ostream& os, 
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  ) const;
private:
  const resolutions _resolution;
  const long _colorized;
  const ulong _hide;
};

class syslog_formatter
{
public:
  syslog_formatter();
  void operator()(
    std::ostream& os, 
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  ) const;
};


}
