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

inline file_writer_options& operator <<= (file_writer_options& self, const file_writer_options& other)
{
  if ( self.path.empty() ) self.path = other.path;
  if ( self.path=="#" ) self.path.clear();
  if ( self.sync==-1 ) self.sync = other.sync;
  
  if ( self.startup_rotate==-1 ) self.startup_rotate = other.startup_rotate;
  if ( self.size_limit==-1 )     self.size_limit = other.size_limit;
  if ( self.time_limit==-1 )     self.time_limit = other.time_limit;
  if ( self.rotation==-1 )       self.rotation = other.rotation;
  return self;
}

struct stdout_writer_options
{
  std::string name;
  int sync = -1;
};

inline stdout_writer_options& operator <<= (stdout_writer_options& self, const stdout_writer_options& other)
{
  if ( self.name.empty() ) self.name = other.name;
  if ( self.name=="#" ) self.name.clear();
  if ( self.sync==-1 ) self.sync = other.sync;
  return self;
}

struct syslog_writer_options
{
  std::string name;
};

inline syslog_writer_options& operator <<= (syslog_writer_options& self, const syslog_writer_options& other)
{
  if ( self.name.empty() ) self.name = other.name;
  if ( self.name=="#" ) self.name.clear();
  return self;
}



}
