//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <mutex>
#include <wlog/logger_fun.hpp>

namespace wlog{

class syslog_writer final
{
public:
  syslog_writer(const std::string& sysname);
  void operator()(
    const time_point& tp,
    const formatter_fun& fmt,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  );
private:
  const std::string _sysname;
};

}
