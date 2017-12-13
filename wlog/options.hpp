//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <wlog/logger_fun.hpp>
#include <wlog/options/formatter_options.hpp>
#include <wlog/writer_options.hpp>

namespace wlog{
  
struct file_logger_options: formatter_options, file_writer_options{};
struct stdout_logger_options: formatter_options, stdout_writer_options{};
struct syslog_logger_options: syslog_writer_options{};

inline file_logger_options& operator <<= (file_logger_options& self, const file_logger_options& other)
{
  static_cast<formatter_options&>(self) <<= static_cast<const formatter_options&>(other);
  static_cast<file_writer_options&>(self) <<= static_cast<const file_writer_options&>(other);
  return self;
}

inline stdout_logger_options& operator <<= (stdout_logger_options& self, const stdout_logger_options& other)
{
  static_cast<formatter_options&>(self) <<= static_cast<const formatter_options&>(other);
  static_cast<stdout_writer_options&>(self) <<= static_cast<const stdout_writer_options&>(other);
  return self;
}

inline syslog_logger_options& operator <<= (syslog_logger_options& self, const syslog_logger_options& other)
{
  static_cast<syslog_writer_options&>(self) <<= static_cast<const syslog_writer_options&>(other);
  return self;
}

struct logger_options: file_logger_options
{
  stdout_logger_options stdout;
  syslog_logger_options syslog;
  
  std::set<std::string> allow;
  std::set<std::string> deny;
};

inline logger_options& operator <<= (logger_options& self, const logger_options& other)
{
  static_cast<file_logger_options&>(self) <<= static_cast<const file_logger_options&>(other);
  self.stdout <<= other.stdout;
  self.stdout <<= static_cast<const formatter_options&>(other);
  if ( self.stdout.sync == -1 ) self.stdout.sync = self.sync;
  if ( self.stdout.name=="#" ) self.stdout.name.clear();
  //self.stdout <<= static_cast<const formatter_options&>(other);
  self.syslog <<= other.syslog;
  if ( self.syslog.name=="#" ) self.syslog.name.clear();
  return self;
}

struct default_logger_options: logger_options
{
  typedef std::map<std::string, logger_options> customize_map;
  customize_map customize;
  
  void upgrade()
  {
    for (auto& op : customize)
      op.second <<= static_cast< const logger_options&>(*this);

    this->stdout <<= static_cast<const formatter_options&>(*this);
    if ( this->stdout.sync == -1 ) this->stdout.sync = this->sync;
    if ( this->stdout.name=="#" )  this->stdout.name.clear();
    if ( this->syslog.name=="#" )  this->syslog.name.clear();
  }

};

struct logger_handlers
{
  formatter_fun file_formatter;
  formatter_fun stdout_formatter;
  formatter_fun syslog_formatter;
  
  writer_fun file_writer;
  writer_fun stdout_writer;
  writer_fun syslog_writer;
};

inline logger_handlers& operator <<= (logger_handlers& self, const logger_handlers& other)
{
  if ( self.file_formatter==nullptr ) self.file_formatter = other.file_formatter;
  if ( self.stdout_formatter==nullptr ) self.stdout_formatter = other.stdout_formatter;
  if ( self.syslog_formatter==nullptr ) self.syslog_formatter = other.syslog_formatter;
  
  if ( self.file_writer==nullptr ) self.file_writer = other.file_writer;
  if ( self.stdout_writer==nullptr ) self.stdout_writer = other.stdout_writer;
  if ( self.stdout_writer==nullptr ) self.stdout_writer = other.stdout_writer;
  return self;
}


struct default_logger_handlers: logger_handlers
{
 typedef std::map<std::string, logger_handlers> customize_map;
 customize_map customize;

  void upgrade()
  {
    for (auto& op : customize)
      op.second <<= static_cast< const logger_handlers&>(*this);
  }
  
};

}
