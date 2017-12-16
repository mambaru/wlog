//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>

namespace wlog{

struct stdout_writer_options
{
  std::string name;
  int sync = -1;

  void upgrade(const stdout_writer_options& other);
  void finalize();
};


}
