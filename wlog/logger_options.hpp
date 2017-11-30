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

namespace wlog{

struct basic_options
{
  /// Включает вывод миллисекунд в поле времени лога
  bool milliseconds = false;
  /// Ограничение на размер файла в байтах
  size_t limit = 0;
  /// Сохрянать лог перед очисткой в <<path>>.log.old
  bool save_old = true;
  /// Перефикс пути к файлу лога. Пустая строка - в файл записи не будет
  /// Если пустая строка в custom_map, то в базовый файл
  std::string path = "";
  /// Вывод в stdout (cout, cerr, clog). Пустая строка - без вывода 
  std::string stdout = "clog";
  /// Имя для системного лога для лога syslog ("" - не используется)
  std::string syslog = "";
  /// Список запрещенных логов или типов сообщений (без учета регистра)
  std::set< std::string > deny;
};

struct options
  : basic_options
{
  typedef std::map<std::string, basic_options> custom_map;
  bool multilog = false;
  custom_map custom;
};


}
