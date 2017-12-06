//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>
#include <fstream>
#include <wlog/logger_fun.hpp>

namespace wlog{

class stdout_writer final
{
public:
  ~stdout_writer();
  stdout_writer(const std::string& stdout, bool sync);
  void operator()(
    const time_point& tp,
    const formatter_fun& fmt,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  ) const;
private:
  std::ostream* _out;
  const bool _sync;
};

}
