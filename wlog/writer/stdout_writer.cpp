//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "stdout_writer.hpp"
#include <ostream>
#include <iostream>
#include <sstream>
#include <mutex>

namespace wlog{
  
stdout_writer::~stdout_writer()
{
  if ( _out != nullptr )
    _out->flush();
}

stdout_writer::stdout_writer(const formatter_fun& fmt, const options& opt)
  : _formatter(fmt)
  , _out(nullptr)
  , _sync(opt.sync!=0)
{
  if (opt.name=="cout")
    _out = &std::cout;
  else if (opt.name=="clog")
    _out = &std::clog;
  else if (opt.name=="cerr")
    _out = &std::cerr;
}

void stdout_writer::operator()(
  const time_point& tp,
  const std::string& name, 
  const std::string& ident,
  const std::string& str
) const
{
  if ( _out != nullptr )
  {
    if ( !_out->good() )
      return;
    if ( _formatter!=nullptr )
      _formatter( *_out, tp, name, ident, str);
    else
      (*_out) << name << " " <<ident<< " " << str;
    if ( _sync )
      _out->flush();
  }
}

}
