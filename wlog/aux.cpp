//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include <chrono>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <syslog.h>

namespace wfc{  namespace core{ namespace aux {

  namespace{

    void prepare( std::string& str, size_t width)
    {
      std::transform(str.begin(), str.end(), str.begin(), [](char ch)->char{ return std::toupper(ch);} );
      if ( width > str.size() )
        std::fill_n( std::back_inserter(str), width - str.size(), ' ' );
    }

    std::string mkms(bool enable)
    {
      if (!enable) return std::string();

      auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
      auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
      auto secround = (millis/1000) * 1000;
      std::stringstream ss;
      ss << "." << std::setfill('0') << std::setw(3)<< millis - secround;
      return ss.str();
    }

    size_t type2pri(const std::string& type)
    {
      if (type=="ERROR")    return LOG_ERR;
      if (type=="WARNING")  return LOG_WARNING;
      if (type=="MESSAGE")  return LOG_NOTICE;
      if (type=="FATAL")    return LOG_ALERT;
      if (type=="BEGIN")    return LOG_INFO;
      if (type=="END")      return LOG_INFO;
      if (type=="DEBUG")    return LOG_DEBUG;
      if (type=="TRACE")    return LOG_DEBUG;
      if (type=="PROGRESS") return LOG_INFO;
      return LOG_ERR;
    }

  } // noname

  std::string mkdate(bool ms)
  {
    time_t ts = time(0);
    struct tm t1;
    localtime_r(&ts, &t1);
    char buf[100];
    int sz = strftime(buf,sizeof(buf), "%Y-%m-%d %H:%M:%S",&t1);
    return std::string(buf,sz) + mkms(ms);
  }
  
  
  void write_to_stream(std::ostream& os, std::string name, std::string ident,  const std::string& str, bool milliseconds )
  {
    prepare(name, 6);
    prepare(ident, 9);
    os << mkdate(milliseconds) << " " << name << " " << ident << " " << str;
  }

  bool replace(std::string& str, const std::string& from, const std::string& to) 
  {
    size_t start_pos = str.find(from);
    if( start_pos == std::string::npos )
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
  }

  void syslog_write(const std::string& sysname, const std::string& type, const std::string& str)
  {
    ::openlog( sysname.c_str(), 0, LOG_USER);
    ::syslog( type2pri(type), str.c_str());
    ::closelog();
  }


  
} } }
