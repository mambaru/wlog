//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once


#include <wlog/logger_fun.hpp>
#include <string>
#include <memory>


namespace wlog{

struct file_writer_options
{
  std::string path;
  int sync = -1;
  int startup_rotate = -1; 
  long size_limit = -1;
  long time_limit = -1;
  long rotation   = -1; // ex save old
};

struct file_writer_handlers
{
};

struct stdout_writer_options
{
  std::string name;
  int sync = -1;
};

struct syslog_writer_options
{
  std::string name;
};


}
