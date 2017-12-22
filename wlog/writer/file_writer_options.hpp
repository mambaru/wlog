//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>

namespace wlog{

struct file_writer_options
{
  std::string path;
  int sync = -1;
  int startup_rotate = -1; 
  long size_limit = -1;
  long time_limit = -1;
  long rotation   = -1; // ex save old
  int rotation_header = -1;
  int rotation_footer = -1;
  int unixtime_suffix = -1;
  void upgrade(const file_writer_options& other);
  void finalize();

};


}
