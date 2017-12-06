//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "stdout_writer.hpp"
#include <ostream>
#include <iostream>
#include <mutex>

namespace wlog{ extern std::mutex stdout_mutex; }

namespace wlog{
  
stdout_writer::~stdout_writer()
{
  if ( _out != nullptr )
    _out->flush();
}

stdout_writer::stdout_writer(const std::string& stdout, bool sync)
  : _out(nullptr)
  , _sync(sync)
{
  if (stdout=="cout")
    _out = &std::cout;
  else if (stdout=="clog")
    _out = &std::clog;
  else if (stdout=="cerr")
    _out = &std::cerr;
}

void stdout_writer::operator()(
  const time_point& tp,
  const formatter_fun& fmt,
  const std::string& name, 
  const std::string& ident,
  const std::string& str
) const
{
  if ( _out != nullptr )
  {
    if ( !_out->good() )
      return;
    std::lock_guard<std::mutex> lk(stdout_mutex);
    if ( fmt!=nullptr )
      fmt( *_out, tp, name, ident, str);
    else
      (*_out) << name << " " <<ident<< " " << str;
    if ( _sync )
      _out->flush();
  }
}

}
