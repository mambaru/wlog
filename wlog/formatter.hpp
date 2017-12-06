//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>
#include <set>

namespace wlog{

class file_formatter
{
public:
  file_formatter(bool milliseconds);
  void operator()(
    std::ostream& os, 
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  ) const;
private:
  const bool _milliseconds;
};

class stdout_formatter
{
public:
  stdout_formatter(bool milliseconds, bool colorized);
  void operator()(
    std::ostream& os, 
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  ) const;
private:
  const bool _milliseconds;
  const bool _colorized;
};

class syslog_formatter
{
public:
  syslog_formatter();
  void operator()(
    std::ostream& os, 
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  ) const;
};


}
