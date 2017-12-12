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

logstream::logstream(logstream&& other)
  : _mutex(other._mutex)
  , _tp(std::move(other._tp))
  , _name(other._name)
  , _ident(other._ident)
  , writer_(other.writer_)
  , _ss()
{}

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
{}

std::string logstream::str() const
{
  return _ss.str();
}

void logstream::write()
{
  std::string msg = _ss.str();

  if ( writer_ != nullptr )
  {
    writer_(_tp, _name, _ident, msg );
  }
/// TODO: перенести в wfc::wfc до инициализации log
#ifndef WLOG_ENABLE_CLOG
  else
  {
    std::clog << _name << " " << _ident << " " << msg;
  }
#endif
  _ss.str(std::string());
  _ss.clear();
}

std::ostream& logstream::operator<< (std::ios& (*pf)(std::ios&))
{
  _ss << pf;
  return _ss;
}
  
std::ostream& logstream::operator<< (std::ios_base& (*pf)(std::ios_base&))
{
  _ss << pf;
  return _ss;
}

std::ostream& logstream::operator<< (std::ostream& (*pf)(std::ostream&))
{
  _ss << pf;
  return _ss;
}

/// ///////////////////////////

stdout_stream::~stdout_stream()
{
  if ( _out.good() )
  {
    _out << _ss.str();
    _out.flush();
  }
  _mutex.unlock();
}

stdout_stream::stdout_stream(stdout_stream&& other)
  : _mutex(other._mutex)
  , _out(other._out)
  , _ss()
{}

stdout_stream::stdout_stream(std::mutex& m, std::ostream& out) 
  : _mutex(m)
  , _out(out)
{}

std::ostream& stdout_stream::operator<< (std::ios& (*pf)(std::ios&))
{
  _ss << pf;
  return _ss;
}
  
std::ostream& stdout_stream::operator<< (std::ios_base& (*pf)(std::ios_base&))
{
  _ss << pf;
  return _ss;
}

std::ostream& stdout_stream::operator<< (std::ostream& (*pf)(std::ostream&))
{
  _ss << pf;
  return _ss;
}

}
