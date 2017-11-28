//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/iwriter.hpp>
#include <mutex>

namespace wlog{

class stdout_writer
  //: public iwriter
{
public:
  stdout_writer(const std::string& stdout);
  void write(const std::string& str);
  
private:
  std::ostream* _out;
};

}
