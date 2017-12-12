//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once
#include <wlog/options.hpp>
#include <wlog/logger_fun.hpp>

#include <string>
#include <memory>
#include <vector>
#include <map>


namespace wlog{

class file_writer;

class default_logger
{
  struct context;
public:
  typedef default_logger_options options;
  typedef default_logger_handlers handlers;

  virtual ~default_logger();
  
  default_logger(default_logger&&);
  explicit default_logger( const options& opt, const handlers& hdr = handlers());
  
  bool operator()(
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& msg
  ) const;
  
private:
  /*
  */
private:  
  
  class impl;
  std::unique_ptr<impl> _impl;
};

}
