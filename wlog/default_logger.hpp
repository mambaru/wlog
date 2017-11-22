//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/ilogger.hpp>
#include <wlog/logger_options.hpp>

namespace wlog{

class default_logger
  : public ilogger
{
public:
  void initialize( const logger_options& opt);
  logger_options options() const;
  // ilogger
  virtual void write(const std::string& name, const std::string& ident, std::string str) override;

private:
  bool is_deny_(const std::string& some) const;
  void write_to_file_(const std::string& name, const std::string& ident,  const std::string& str);
  void write_to_stdout_(const std::string& name, const std::string& ident,  const std::string& str);
  void write_to_syslog_( const std::string& ident,  const std::string& str);
  
private:
  std::string _filename;
  logger_options _conf;
};

}
