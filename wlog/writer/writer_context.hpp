//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/writer/file_writer_options.hpp>
#include <wlog/logger_fun.hpp>
#include <wlog/types.hpp>
#include <list>
#include <ctime>
#include <string>

namespace wlog{

struct writer_context
{
  typedef file_writer_options options_type;

  const time_point start_time;
  const formatter_fun formatter;
  options_type options;

  size_t summary_size;
  size_t rotation_counter;
  time_t rotate_time;
  std::string current_path;
  std::list<std::string> path_list;
  
  writer_context(const formatter_fun& fmt, const options_type& opt )
    : start_time(time_point::clock::now())
    , formatter(fmt)
    , options(opt)
    , summary_size(0)
    , rotation_counter(0)
    , rotate_time(0)
  {}
};

  
}
