//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "formatter.hpp"
#include <iomanip>
#include <string>
#include <algorithm>
#include <sstream>
#include <chrono>

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

  std::string mkdate()
  {
    time_t ts = time(0);
    struct tm t1;
    localtime_r(&ts, &t1);
    char buf[100];
    int sz = strftime(buf,sizeof(buf), "%Y-%m-%d %H:%M:%S",&t1);
    return std::string(buf,sz);
  }
}
  
formatter::formatter(bool milliseconds, const std::vector< std::string >& deny)
  : _milliseconds(milliseconds)
  , _deny(deny)
{
  std::sort( _deny.begin(), _deny.end() );
}

std::string formatter::format(const std::string& name, const std::string& ident, const std::string& str)
{
  if (is_deny_(name) || is_deny_(ident))
    return "";
  
  std::stringstream ss;
  ss << mkdate();
  if ( _milliseconds )
    ss << "." << mkms();
  ss << " " << name << " " << ident << " " << str;
  return ss.str();
}

bool formatter::is_deny_(const std::string& some) const
{
  if ( _deny.empty() )
    return false;
  
  return std::find( _deny.begin(), _deny.end(), some ) != _deny.end();
}

  
}
