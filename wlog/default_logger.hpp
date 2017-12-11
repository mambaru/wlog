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
  typedef default_logger_options options;
  typedef default_logger_handlers handlers;

  struct context
  {
    std::set<std::string> allow;
    std::set<std::string> deny;
    writer_fun file_writer;
    writer_fun stdout_writer;
    writer_fun syslog_writer;
  };

  explicit default_logger( const options& opt, const handlers& hdr = handlers());
  
  bool operator()(
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& msg
  ) const;
  
private:
  
  void init_context_();
  /*
  void init_handlers_(
    logger_handlers& hdr, 
    const logger_handlers& opt
  );
  */

  void inherit_options_(
    const std::string& name,
    logger_options& bopt, 
    const logger_options& opt
  );
  
  bool allow_(
    const std::string& name,
    const std::string& ident, 
    const std::set<std::string>& allow,
    const std::set<std::string>& deny
  ) const;
  
private:  
  typedef std::string key_type;
  typedef context _common;
  typedef std::map<key_type, context > context_map;
  typedef std::shared_ptr<file_writer> file_writer_ptr;

  context_map _customize;
  std::map< std::string, file_writer_ptr > _file_map;
  /*
  typedef std::map<key_type, std::vector<after_fun> > after_map;
  typedef std::map<key_type, logger_options > options_map;
  typedef std::map<key_type, logger_handlers > handlers_map;
  logger_options _default_options;
  logger_handlers _default_handlers;
  options_map _options_map;
  handlers_map _handlers_map;
  after_map  _after_map;

  */
};

}
