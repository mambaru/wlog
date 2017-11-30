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

void stdout_writer::operator()( const std::string& str)
{
  if ( _out != nullptr )
  {
    (*_out) << str;
    _out->flush();
  }
}

}
