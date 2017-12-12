//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <mutex>
#include <wlog/logger_fun.hpp>
#include <wlog/writer_options.hpp>

namespace wlog{

class syslog_writer final
{
public:
  typedef syslog_writer_options options;
  syslog_writer(const formatter_fun& formatter, const options& opt);
  void operator()(
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  );
private:
  formatter_fun _formatter;
  const std::string _sysname;
};

}
