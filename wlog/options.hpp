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

struct basic_options
{
  /// Включает вывод миллисекунд в поле времени лога
  bool milliseconds = true;
  /// Ограничение на размер файла в байтах
  /// -1 наследуется или без ограничения
  /// 0 без ограничения
  long limit = -1;
  /// Сохрянать лог перед очисткой в <<path>>.log.old-N
  /// -1 наследуется или не сохранять
  /// 0 не сохранять
  long save_old = -1;
  bool sync = true;
  bool colorized = true;
  /// Файл лога. Пустая строка - в файл записи не будет
  /// Если пустая строка в custom_map, то в базовый файл
  std::string path = "";
  /// Вывод в stdout (cout, cerr, clog). Пустая строка - без вывода 
  std::string stdout = "clog";
  /// Имя для системного лога для лога syslog ("" - не используется)
  std::string syslog = "";
  /// Список запрещенных логов или типов сообщений 
  std::set< std::string > deny;
  /// Список разрешенных логов или типов сообщений (остальные запрещены)
  std::set< std::string > allow;
  
  // Пользовательский варианты формирования сообщений и записи
  // Если заданы, то используються они, а соответствующие опции игнорируются
  customize_handlers handlers;
};

struct options
  : basic_options
{
  typedef std::map<std::string, basic_options> customize_map;
  customize_map customize;
};


}
