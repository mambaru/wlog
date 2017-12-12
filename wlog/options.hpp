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
#include <wlog/formatter_options.hpp>
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
  self.syslog <<= other.syslog;
  return self;
}

struct default_logger_options: logger_options
{
  typedef std::map<std::string, logger_options> customize_map;
  customize_map customize;
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
};


/*
struct customize_handlers
{
  formatter_fun file_formatter;
  formatter_fun stdout_formatter;
  formatter_fun syslog_formatter;
  
  writer_fun file_writer;
  writer_fun stdout_writer;
  writer_fun syslog_writer;
  
  std::vector<after_fun> after;
};

struct customize_options
 : customize_handlers
{
  /// Список запрещенных логов или типов сообщений 
  std::set< std::string > deny;
  /// Список разрешенных логов или типов сообщений (остальные запрещены)
  std::set< std::string > allow;
};

struct basic_formatter_options
{
  /// Включает вывод миллисекунд в поле времени лога
  resolutions resolution = resolutions::inherited;

  long colorized = -1;

  unsigned long hide = ~0ul;
};

struct formatter_options
{
  /// Включает вывод миллисекунд в поле времени лога
  resolutions resolution = resolutions::inherited;

  long colorized = -1;

  unsigned long hide = ~0ul;
  
  // date formatter
  // time formatter
  // name formatter
  // ident formatter
  // message formatter
  
  formatter_fun formatter;
};

struct file_writer_options
  :  formatter_options
{
  /// Ограничение на размер файла в байтах
  /// -1 наследуется или без ограничения
  /// 0 без ограничения
  long limit = -1;
  /// Сохрянать лог перед очисткой в <<path>>.log.old-N
  /// -1 наследуется или не сохранять
  /// 0 не сохранять
  long save_old = -1;

  bool sync = true;
  
  /// Файл лога. Пустая строка - в файл записи не будет
  /// Если пустая строка в custom_map, то в базовый файл
  std::string path = "";
  
  writer_fun writer;
};

struct stdout_writer_options
  :  formatter_options
{
  bool sync = true;
  std::string stdout = "";
};


struct basic_options
  : customize_options
{
  resolutions resolution = resolutions::inherited;

  long colorized = -1;

  unsigned long hide = ~0ul;

  /// Ограничение на размер файла в байтах
  /// -1 наследуется или без ограничения
  /// 0 без ограничения
  long limit = -1;
  /// Сохрянать лог перед очисткой в <<path>>.log.old-N
  /// -1 наследуется или не сохранять
  /// 0 не сохранять
  long save_old = -1;
  bool sync = true;
  /// Файл лога. Пустая строка - в файл записи не будет
  /// Если пустая строка в custom_map, то в базовый файл
  std::string path = "";
  /// Вывод в stdout (cout, cerr, clog). Пустая строка - без вывода 
  std::string stdout = "clog";
  /// Имя для системного лога для лога syslog ("" - не используется)
  std::string syslog = "";
};

struct options
  : basic_options
{
  typedef std::map<std::string, basic_options> customize_map;
  customize_map customize;
};
*/

}
