//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once
#include <wlog/options.hpp>
#include <wlog/logger_fun.hpp>
#include <mutex>
#include <memory>

namespace wlog{

class file_writer;

class default_logger
{
public:
  explicit default_logger( const options& opt);
  bool operator()(    const char* name, 
    const char* ident,
std::string str) const;
  
private:
  void init_handlers_(customize_handlers& handlers, const basic_options& opt) ;
  void inherit_options_(const std::string& name, basic_options& bopt, const basic_options& opt);

private:  
  typedef std::string key_type;
  typedef std::map<key_type, std::vector<after_fun> > after_map;
  typedef std::map<key_type, customize_handlers > handler_map;
  customize_handlers _default_handlers;
  handler_map _handler_map;
  after_map  _after_map;

  typedef std::shared_ptr<file_writer> file_writer_ptr;
  std::map< std::string, file_writer_ptr > _file_writer;
};

}
