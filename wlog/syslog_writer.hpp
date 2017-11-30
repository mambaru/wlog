//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <mutex>

namespace wlog{

class syslog_writer
{
public:
  syslog_writer(const std::string& sysname);
  void operator()(const std::string& ident, const std::string& str);
private:
  const std::string _sysname;
};

}
