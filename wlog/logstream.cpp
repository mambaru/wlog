//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "logstream.hpp"
#include <iostream>
#include <mutex>
namespace wlog {

logstream::~logstream()
{
  this->write();
  _mutex.unlock();
}

logstream::logstream(
  std::mutex& m,
  const std::string& name,
  const std::string& ident,
  const logger_fun& writer
) : _mutex(m)
  , _tp(time_point::clock::now())
  , _name( name )
  , _ident( ident )
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
    flag = writer_(_tp, _name, _ident, msg);
  }
#ifndef WLOG_ENABLE_CLOG
  else
  {
    std::clog << _name << " " << _ident << " " << msg;
  }
#endif
  _ss.clear();
  return flag;
}


}
