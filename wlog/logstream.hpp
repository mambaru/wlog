//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/logger_fun.hpp>
#include <sstream>
#include <string>
#include <memory>

namespace wlog{

class logstream
{
public:
  ~logstream();
  
  logstream(const logstream& ll) = delete;
  
  logstream& operator = (logstream& ll) = delete;
  
  logstream(logstream&& ll);

  logstream& operator = (logstream&& ll) = delete;
  
  logstream(const std::string& name, const std::string& type, const logger_fun& writer);

  logstream(std::string&& name, std::string&& type, const logger_fun& writer);

  std::string str() const;
  
  bool write();

  template<typename V>
  std::stringstream& operator << ( const V&  v)
  {
    _ss<<v;
    return _ss;
  }

private:
  std::string _name;
  std::string _type;
  std::stringstream _ss;
  const logger_fun& writer_;
};

}
