//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once
#include <wlog/options.hpp>
#include <wlog/logger_fun.hpp>
#include <mutex>

namespace wlog{

class default_logger
{
public:
  default_logger( const options& opt);
  bool operator()(const std::string& name, const std::string& ident, std::string str);
  
private:
  formatter_fun get_formatter_(const std::string& name) ;
  writer_fun get_file_writer_(const std::string& name) ;
  writer_fun get_stdout_writer_(const std::string& name) ;
  syslog_fun get_syslog_writer_(const std::string& name) ;
private:
  typedef std::string key_type;
  typedef std::map<key_type, formatter_fun> formatter_map;
  typedef std::map<key_type, writer_fun> writer_map;
  typedef std::map<key_type, syslog_fun> syslog_map;
  
  options _opt;
  typedef std::mutex mutex_type;
  formatter_fun _default_formatter;
  writer_fun _default_file_writer;
  writer_fun _default_stdout_writer;
  syslog_fun _default_syslog_writer;
  
  formatter_map _formatter_map;
  writer_map _file_map;
  writer_map _stdout_map;
  syslog_map _syslog_map;
};

}
