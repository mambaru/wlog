//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "logstream.hpp"
#include <iostream>

namespace wlog {

logstream::~logstream()
{
  this->write();
}
/*
logstream::logstream(logstream&& ll)
  : _name(std::move(ll._name))
  , _type(std::move(ll._type))
  , _ss()
  , writer_(std::move(ll.writer_))
{
}
*/

/*
logstream& logstream::operator = (logstream&& ll)
{
  _name = std::move(ll._name);
  _type = std::move(ll._type);
  _ss.clear();
  writer_ = ll.writer_;
  return *this;
}
*/

logstream::logstream(const std::string& name, const std::string& type, const logger_fun& writer)
  : _name(name)
  , _type(type)
  , writer_(writer)
{
}

logstream::logstream(std::string&& name, std::string&& type, const logger_fun& writer)
  : _name( std::move(name) )
  , _type( std::move(type) )
  , writer_(writer)
{
}

std::string logstream::str() const
{
  return _ss.str();
}

bool logstream::write()
{
  bool flag = false;
  std::string msg = _ss.str();
  if ( msg.empty() )
    return flag;
  
  if ( writer_ != nullptr )
  {
    flag = writer_(_name, _type, msg);
  }
#ifndef WLOG_ENABLE_CLOG
  else
  {
    std::clog << _name << " " << _type << " " << msg;
  }
#endif
  _ss.clear();
  return flag;
}


}
