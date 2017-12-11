//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <mutex>
#include <memory>
#include <wlog/logger_fun.hpp>
#include <fstream>

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

class file_writer final
{
public:
  ~file_writer();
  typedef file_writer_options options;
  typedef file_writer_handlers handlers;
  
  file_writer(const formatter_fun& formatter, const options& opt, const handlers& hdlr = handlers() );
  
  void operator()(  
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  );
  
private:
  void write_(  
    std::ofstream& oflog,
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  );
  
  bool rotate_if_( std::ofstream& oflog);
  void rotate_( std::ofstream& oflog);

  formatter_fun _formatter;
  options _opt;
  handlers _handlers;
  /*
  typedef std::mutex mutex_type;
  const std::string _path;
  const bool _sync;
  const long _limit;
  const int _save_old;
  */
  long _save_count;
  long _summary;
  time_t _rotate_time;
  //time_t _file_time;
  const std::string _starttime;
  //mutex_type _mutex;
  std::ofstream _oflog;
};

}
