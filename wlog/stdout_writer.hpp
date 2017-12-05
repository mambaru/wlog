//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>
#include <ostream>
#include <wlog/logger_fun.hpp>

namespace wlog{

class stdout_writer
{
public:
  stdout_writer(const std::string& stdout);
  void operator()(
    const formatter_fun& fmt,
    const char* name, 
    const char* ident,
    const std::string& str
  );
private:
  std::ostream* _out;
};

}
