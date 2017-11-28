//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/iwriter.hpp>
#include <mutex>

namespace wlog{

class syslog_writer
  : public iwriter
{
public:
  syslog_writer(const std::string& sysname, int pri);
  virtual void write(const std::string& str) override;
  
private:
  const std::string _sysname;
  const int _pri;
};

}
