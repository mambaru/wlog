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
public:
  explicit default_logger( const options& opt);
  
  bool operator()(
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& msg
  ) const;
  
private:
  void init_handlers_(
    customize_handlers& handlers, 
    const basic_options& opt
  );

  void inherit_options_(
    const std::string& name, 
    basic_options& bopt, 
    const basic_options& opt
  );
  
  bool allow_(
    const std::string& name,
    const std::string& ident, 
    const std::set<std::string>& allow,
    const std::set<std::string>& deny
  ) const;
  
private:  
  typedef std::string key_type;
  typedef std::map<key_type, std::vector<after_fun> > after_map;
  typedef std::map<key_type, customize_options > options_map;
  customize_options _default_options;
  options_map _options_map;
  after_map  _after_map;

  typedef std::shared_ptr<file_writer> file_writer_ptr;
  std::map< std::string, file_writer_ptr > _file_writer;
};

}
