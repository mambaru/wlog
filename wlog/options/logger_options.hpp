//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/options/basic_logger_options.hpp>
#include <string>
#include <map>

namespace wlog{
  
struct logger_options: basic_logger_options
{
  typedef std::map<std::string, basic_logger_options> customize_map;
  customize_map customize;
  
  logger_options()
  {
    formatter_options::resolution = resolutions::seconds;
    formatter_options::hide = hide_flags::none;
    formatter_options::colorized = colorized_flags::none;
    
    file_writer_options::startup_rotate = 0;
    file_writer_options::size_limit = 0;
    file_writer_options::time_limit = 0;
    file_writer_options::rotation = 0;
    file_writer_options::sync = 1;
    
    basic_logger_options::stdout.name = "clog";
    //basic_logger_options::stdout.colorized = colorized_flags::all;
    basic_logger_options::stdout.colorized = colorized_flags::all;
  }
  
  void upgrade()
  {
    for (auto& op : customize)
      op.second <<= static_cast< const basic_logger_options&>(*this);

    this->stdout <<= static_cast<const formatter_options&>(*this);
    if ( this->stdout.sync == -1 ) this->stdout.sync = this->sync;
    if ( this->stdout.name=="#" )  this->stdout.name.clear();
    if ( this->syslog.name=="#" )  this->syslog.name.clear();
  }
};


}
