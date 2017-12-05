//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "stdout_writer.hpp"
#include <ostream>
#include <iostream>
#include <mutex>

namespace wlog{
  
extern std::mutex stdout_mutex;
  
stdout_writer::stdout_writer(const std::string& stdout)
  : _out(nullptr)
{
  if (stdout=="cout")
    _out = &std::cout;
  else if (stdout=="clog")
    _out = &std::clog;
  else if (stdout=="cerr")
    _out = &std::cerr;
}

void stdout_writer::operator()(
  const formatter_fun& fmt,
  const char* name, 
  const char* ident,
  const std::string& str
)
{
  if ( _out != nullptr )
  {
    std::lock_guard<std::mutex> lk(stdout_mutex);
    if ( fmt!=nullptr )
      fmt( *_out, name, ident, str);
    else
      (*_out) << name << " " <<ident<< " " << str;
    _out->flush();
  }
}

}
