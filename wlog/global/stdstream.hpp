//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/types.hpp>
#include <sstream>
#include <ostream>
#include <string>

namespace wlog{

class stdstream final
{
public:
  ~stdstream();
  
  stdstream(const stdstream& other) = delete;
  
  stdstream& operator = (stdstream& other) = delete;

  stdstream& operator = (stdstream&& other) = delete;

  stdstream(stdstream&& other);
  
  stdstream(mutex_type& m, std::ostream& out);
  
  std::ostream& log();

private:
  mutex_type& _mutex;
  std::ostream& _out;
  std::stringstream _ss;
};

}
