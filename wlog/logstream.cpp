//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "logstream.hpp"
#include <iostream>
#include <mutex>
#include <cassert>
namespace wlog {

class logstream::impl
{
public:
  ~impl();
  impl(std::mutex& m, const std::string& name, const std::string& ident, const logger_fun& writer);
  std::string str() const;
  std::ostream& log();

private:
  std::mutex& _mutex;
  const time_point _tp;
  const std::string _name;
  const std::string _ident;
  const logger_fun writer_;
  std::stringstream _ss;
};

logstream::impl::~impl()
{
  if ( writer_ != nullptr )
  {
    writer_(_tp, _name, _ident, _ss.str() );
  }
/// TODO: перенести в wfc::wfc до инициализации log
#ifndef WLOG_ENABLE_CLOG
  else
  {
    std::clog << _name << " " << _ident << " " << _ss.str();
  }
#endif
  _mutex.unlock();
}

logstream::impl::impl(
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

std::string logstream::impl::str() const
{
  return _ss.str();
}

std::ostream& logstream::impl::log() 
{
  return _ss;
}

logstream::~logstream()
{
  _impl.reset();
}

logstream::logstream(logstream&& other)
  : _impl( std::move(other._impl) )
{}

logstream::logstream(
  std::mutex& m,
  const std::string& name,
  const std::string& ident,
  const logger_fun& writer
) : _impl(new impl(m, name, ident, writer) )
{}

std::string logstream::str() const
{
  assert(_impl!=nullptr);
  return _impl->str();
}

std::ostream& logstream::log() 
{
  assert(_impl!=nullptr);
  return _impl->log();
}


/// ///////////////////////////

stdstream::~stdstream()
{
  if ( _out.good() )
  {
    _out << _ss.str();
    _out.flush();
  }
  _mutex.unlock();
}

stdstream::stdstream(stdstream&& other)
  : _mutex(other._mutex)
  , _out(other._out)
  , _ss()
{}

stdstream::stdstream(std::mutex& m, std::ostream& out) 
  : _mutex(m)
  , _out(out)
{}

std::ostream& stdstream::log() { return _ss;}


}
