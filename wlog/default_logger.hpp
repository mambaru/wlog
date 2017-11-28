//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once
#include <wlog/logger_options.hpp>
#include <wlog/logger_fun.hpp>
#include <mutex>

namespace wlog{

class default_logger
{
public:
  void initialize( const options& opt);
  void write(const std::string& name, const std::string& ident, std::string str);
  
private:
  formatter_fun get_formatter_(const std::string& name, const std::string& ident) const;
  writer_fun get_file_writer_(const std::string& name, const std::string& ident) const;
  writer_fun get_stdout_writer_(const std::string& name, const std::string& ident) const;
  writer_fun get_syslog_writer_(const std::string& name, const std::string& ident) const;
private:
  options _opt;
  typedef std::mutex mutex_type;
  formatter_fun _default_formatter;
  writer_fun _default_file_writer;
  writer_fun _default_stdout_writer;
  writer_fun _default_syslog_writer;
  mutex_type _mutex;
};

}
