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
#include <wlog/resolutions.hpp>

namespace wlog{
  
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


}
