//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>
#include <fstream>
#include <wlog/logger_fun.hpp>
#include <wlog/writer_options.hpp>

namespace wlog{

class stdout_writer final
{
public:
  typedef stdout_writer_options options;
  ~stdout_writer();
  stdout_writer(const formatter_fun& fmt, const options& opt);
  void operator()(
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  ) const;
private:
  formatter_fun _formatter;
  std::ostream* _out;
  const bool _sync;
};

}
