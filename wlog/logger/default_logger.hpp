//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once
#include <wlog/logger/logger_options.hpp>
#include <wlog/logger/logger_handlers.hpp>
#include <wlog/logger_fun.hpp>

#include <string>
#include <memory>
#include <vector>
#include <map>


namespace wlog{

class default_logger
{
public:
  typedef logger_options options;
  typedef logger_handlers handlers;

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
  
  class impl;
  std::unique_ptr<impl> _impl;
};

}
