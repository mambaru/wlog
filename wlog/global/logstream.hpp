//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logger_fun.hpp>
#include <wlog/types.hpp>
#include <string>
#include <memory>

namespace wlog{

class logstream final
{
public:
  ~logstream();
  
  logstream(const logstream& other) = delete;
  
  logstream& operator = (logstream& other) = delete;

  logstream& operator = (logstream&& other) = delete;

  logstream(logstream&& other);
  
  logstream(mutex_type& m, const std::string& name, const std::string& ident, const logger_fun& writer);
  
  std::string str() const;
  
  std::ostream& log();

private:
  class impl;
  std::unique_ptr<impl> _impl;
};

}
