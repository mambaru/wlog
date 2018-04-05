//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017, 2018
//
// Copyright: See COPYING file that comes with this distribution
//

#include "stdstream.hpp"

namespace wlog {

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

stdstream::stdstream(mutex_type& m, std::ostream& out) 
  : _mutex(m)
  , _out(out)
{
  _mutex.lock();
}

std::ostream& stdstream::log() { return _ss;}


}
