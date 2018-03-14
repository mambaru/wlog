Библиотека логгирования и WFC-фреймворка, с большими возможностия кастомизации с помощью опций, обработчиков и конфигурационного файла в формате JSON.

![wlog](https://i.imgur.com/xdC2tVt.png)

Каждая строка лога состоит из временной отметки, имени лога (по умолчанию WLOG), типа сообщения и текста сообщения. Запись в лог осуществляеться с помощью набора макросов, например:
```cpp
#define WLOG_ENABLE_DEBUG_LOG // Don't disable DEBUG and TRACE in Release 

#include <wlog/wlog.hpp>
#include <wlog/init.hpp>

int main()
{
  wlog::init("example.log"); 
  WLOG_MESSAGE( "Example N" << 1 << " message" )
  WLOG_WARNING( "Example N" << 1 << " warning" )
  WLOG_ERROR( "Example N" << 2 << " error" )
  WLOG_DEBUG( "Example N" << 3 << " debug" )
  WLOG_TRACE( "Example N" << 4 << " trace" )
  return 0;
}
```
По умолчаню сообщения DEBUG и TRACE отключаются на уровне препроцессора в Release режиме.

# Системные требования и особенности

* linux
* g++ 4.7 и выше, clang++
* cmake 2.8 и выше
* Стандарт c++11
* thread-safe
* Запись в файлы, stdout и syslog
* **Не** header-only 
* Большие возможности кастомизации форматирования и ротирования как на уровне конфигурации, так и с помощью програмных обработчиков 
* Можно писать наборы логов в разные файлы с различным форматированием (в том числе stdout) и режимами ротации
* Динамическое реконфигурирование в любой момент времени 
* Поддержка JSON-конфигурации с комментариями в Си-стиле

# Сборка и установка

```bash
make shared && sudo make install
make static && sudo make install
```

Для сборки примеров и тестов, а также чтобы отключить поддержку JSON-конфигурации:

```bash
git clone https://github.com/mambaru/wlog.git
mkdir wlog/build
cd wlog/build
cmake ..
# Для сборки примеров и тестов
cmake -DBUILD_TESTING=ON ..
# Если поддержка JSON не требуется 
cmake -DWLOG_DISABLE_JSON=ON ..
cmake --build make
ctest 
```

Для компиляции с поддержкой JSON-конфигурации потребуются header-only библиотеки wjson и faslib, которые система сборки автоматически клонирует 
в директорию сборки, если не найдет их в системе или на том же уровне файловой системы, куда вы клонировали wlog, но для использования они 
не нужны.

## Подключение как submodule

main.cpp:
```cpp
#include <wlog/logging.hpp>
#include <wlog/init.hpp>
#include <wlog/load.hpp>

int main()
{
  wlog::init(wlog::load("{}"));
  WLOG_MESSAGE("Hello")
}
```

### Если нужен только wlog
CMakeLists.txt:
```cmake
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")
add_subdirectory(wlog)
add_executable(main main.cpp)
include_directories(wlog)
target_link_libraries(main wlog)
```

```bash
git init
git submodule add https://github.com/mambaru/wlog.git
mkdir build
cd build
cmake ..
make
```

### С подключение faslib и wjson
CMakeLists.txt:
```cmake
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")
add_subdirectory(faslib)
add_subdirectory(wjson)
add_subdirectory(wlog)
include_directories(wlog wjson faslib)
add_executable(main main.cpp)
target_link_libraries(main wlog)
```

```bash
git init
git submodule add https://github.com/migashko/faslib.git
git submodule add https://github.com/mambaru/wjson.git
git submodule add https://github.com/mambaru/wlog.git
mkdir build
cd build
cmake ..
make
```

# Инициализация

Если не вызвать `wlog::init` то вывод будет на экран без форматирования и синхронизации. Вызывать `wlog::init` можно в любое время в любом месте, 
а также повторно для реконфигурации. 

```cpp
#include <wlog/init.hpp>
#include <wlog/load.hpp>

  // По умолчанию вывод только в clog в цвете
  wlog::init();
  // Выводить с тысячными долями секунд и отключить цветовую раскраску 
  wlog::init(wlog::resolutions::milliseconds, wlog::colorized_flags::none);
  // Выводить в файл и clog
  wlog::init("main.log");
  // Выводить с тысячными долями секунд в файл и clog и отключить цветовую раскраску для clog
  wlog::init("main.log", wlog::resolutions::milliseconds, wlog::colorized_flags::none);

  // Так можно задать все остальные опции
  wlog::logger_options opt;
  opt.path="main.log";
  wlog::init(opt);

  // Загрузть конфигурацию из файла
  wlog::init(wlog::load("logger.json"));
  // Загрузть конфигурацию из строки
  wlog::init(wlog::load("{\"path\":\"main.log\"}"));

  // Вариант с проверкой 
  std::string err;
  opt = wlog::logger_options();
  if ( wlog::load("logger.json", &opt, &err) )
    wlog::init(opt);
  else
    std::cerr << "ERROR: " << err << std::endl;
```

Для вывода финального сообщения при завершении работы:
```cpp
  // Выключаем логгирование 
  if (auto log = wlog::release() )
  {
    // Глобальный лог уже не доступен
    // Но можем записать в лог финальное сообщение
    log( wlog::time_point::clock::now(), "EXAMPLE4", "FINAL", "Bye!\n" );
  }
```
Это может быть полезно, если нужна гарантия, что сообщение будет последним в файле лога (напрмер в многопоточной среде, и/или много отладочных сообщений в деструкторах объектов)

# Использование

В каждом сообщении лога присутствуют четыре основные элемента, которые можно кастомизировать или скрывать:

* Дата и время + доли секунды
* Имя лога
* Тип сообщения:
  * ERROR   - ошибки, после которых система сохраняет работоспособность и согласованность данных 
  * WARNING - предупреждения, например о превышении размера очереди. 
  * MESSAGE - прочие уведомления
  * FATAL   - фатальная ошибка. Обычно далее следует останов системы
  * BEGIN   - начало какого либо процесса (например загрузка БД)
  * END     - окончание какого либо процесса (например загрузка БД)
  * DEBUG   - отладочные сообщения (отключается в релиз-версии на уровне препроцессора )
  * TRACE   - трассировка ввода/вывода (отключается в релиз-версии на уровне препроцессора )
  * PROGRESS - трассировка прогресса длительных операций без перевода строки (например процент загрузки БД)
* Сообщение. Произвольный формат
 
По умолчанию используется лог WLOG в соответствующем наборе макросов:
 
```cpp
//wlog/logging.hpp
#define WLOG_ERROR(X)    WLOG_LOG_ERROR   ( "WLOG", X )
#define WLOG_WARNING(X)  WLOG_LOG_WARNING ( "WLOG", X )
#define WLOG_MESSAGE(X)  WLOG_LOG_MESSAGE ( "WLOG", X )
#define WLOG_FATAL(X)    WLOG_LOG_FATAL   ( "WLOG", X )
#define WLOG_BEGIN(X)    WLOG_LOG_BEGIN   ( "WLOG", X )
#define WLOG_END(X)      WLOG_LOG_END     ( "WLOG", X )
#define WLOG_DEBUG(X)    WLOG_LOG_DEBUG   ( "WLOG", X )
#define WLOG_TRACE(X)    WLOG_LOG_TRACE   ( "WLOG", X )
#define WLOG_PROGRESS(X) WLOG_LOG_PROGRESS( "WLOG", X )
```
Аналогичным образом можно сделать свой набор макросов для каждого лога. Если не устраивает предлагаемых сообщений, то можно задать свой, аналогично набору макросов для работы с syslog:

```cpp
//wlog/logging.hpp
#define WSYSLOG_EMERG(X)   WLOG( "SYSLOG", "EMERG",   X)
#define WSYSLOG_ALERT(X)   WLOG( "SYSLOG", "ALERT",   X)
#define WSYSLOG_CRIT(X)    WLOG( "SYSLOG", "CRIT",    X)
#define WSYSLOG_ERR(X)     WLOG( "SYSLOG", "ERR",     X)
#define WSYSLOG_WARNING(X) WLOG( "SYSLOG", "WARNING", X)
#define WSYSLOG_NOTICE(X)  WLOG( "SYSLOG", "NOTICE",  X)
#define WSYSLOG_INFO(X)    WLOG( "SYSLOG", "INFO",    X)
#define WSYSLOG_DEBUG(X)   WLOG( "SYSLOG", "DEBUG",   X)
```
Пример использования:
```cpp
WLOG_MESSAGE("Это " << 10 << " сообщение" )
WLOG_ERROR("Это " << 25 << " ошибка" )
```

# Конфигурирование

Здесь и далее будут приводиться примеры конфигурации в JSON-формате. Имена полей полностью совпадают с полями структур конфигурации. 
В неочевидных случаях, например при использовании перечислений, будут приведены примеры на C++.
JSON-конфигурация, со значениями по умолчанию. Если заначения по умолчаню вас устраивают, то эти поля можно удалять:
```cpp
{
  /* Список доступных логов и типов сообщений */
  "allow": [],
  /* Список запрещенных логов и типов сообщений */
  "deny": [],
  /* Путь к файлу лога */
  "path": "",
  /* Синхронная запись (открыть-записать-закрыть) */
  "sync": true,

  /* --- Опции ротации --- */

  /* Начинать лог с начала файла (старый лог сохраняется, если задан rotation) */
  "startup_rotate": false,
  /* Ограничение лога по размеру (в байтах) */
  "size_limit": 0,
  /* Ограничение лога по времени (в секундах) */
  "time_limit": 0,
  /* Включить сохранение логов при ротации (макс. кол-во файлов) */
  "rotation": 0,
  /* Сопроводительное сообщение ротирование в начале файла */
  "rotation_header": true,
  /* Сопроводительное сообщение ротирование в конце файла */
  "rotation_footer": true,
  /* По умолчание к имени файла добавляется внутренний счетчи, если указать эту функцию - то unixtime*/
  "unixtime_suffix": false,

  /* --- Опции форматирования --- */
  // Ширина поля имени лога (в символах)
  "name_width": 6,
  // Ширина поля типа сообщения (в символах)
  "ident_width": 9,
  /* Точность отображения времени (от наносекунд до года)  */
  "resolution": "seconds",
  /* Формат представления даты и времени в формате strftime (игнорируется если заданы resolution или hide) */
  "datetime_format": "",
  /* Перечисление скрываемых частей сообщения */
  "hide": "none",
  /* Локаль */
  "locale": "",
  /* Включить цветовую схему при записи в файл */
  "colorized": "none",
  /* Карта цветов*/
  "color_map": {},
    
  /* --- Кастомизация --- */
    
  /* Настройки стандартного вывода */
  "stdout": { 
    /* Возможные значения: cout, clog, cerr и # для запрета вывода */
    "name":"cout",
    /* Делать flush после каждого сообщения */
    "sync": false,
    /* Включить цветовую схему при записи в stdout */
    "colorized": "all",
    /* -- остальные опции форматирования -- */
  },
  /* Настройки записи в системный лог */
  "syslog": {
    /* Имя для syslog. Если не указан (по умолчанию) то запись в syslog не ведется*/
    "name":""
  },
  /* Индивидуальные настройки для логов и типов сообщений */
  "customize": [ /* рассмотрим далее */ ]
}
```
Минимальная конфигурация:
```cpp
{}
```
В этом случае запись в файл и syslog не производится, а вывод только в ```std::cout``` в цвете. Чтобы отключить раскраску:
```cpp
{
  "stdout": { 
    "colorized": "none",
  }
}
```
Для записи в файл достаточно указать путь:
```cpp
{
  "path":"/path/to/log/file.log" 
}
```
Чтобы запретить вывод в stdout, а в файл выводить в цвете:
```cpp
{
  "path":"/path/to/log/file.log" 
  "colorized": "none",
  "stdout": { 
    "name":"#"
  }
}
```
Чтобы запретить запись сообщений конкретного лога или типов сообщений всех логов, нужно перечислить их в массиве `deny`, например для того чтобы отфильтровать "мусор" в Debug режиме:
```cpp
{
  "path": "/path/to/log/file.log",
  "deny": ["DEBUG", "TRACE"]
}
```
Чтобы разрешить запись сообщений конкретного лога или некоторые типы сообщений, нужно перечислить их в массиве `allow`, например для того чтобы разрешить только сообщения лога MYLOG, и сообщения ERROR остальных логов:
```cpp
{
  "path": "/path/to/log/file.log",
  "deny": ["MYLOG", "ERROR"]
}
```
Ускорить запись в лог примерно в три раза, но без гарантий в случае аварийных падений:
```cpp
{
  "path": "/path/to/log/file.log",
  "sync": false
}
```
## Настройки ротации

По умолчанию запись происходит в один и тот же файл, без ограничений. Чтобы при каждом запуске запись происходила с начала файла:
```cpp
{
  "path": "/path/to/log/file.log",
  "startup_rotate": true
}
```
Чтобы при этом сохранялся лог от предыдущего запуска в файле `/path/to/log/file.log.old-0`:
```cpp
{
  "path": "/path/to/log/file.log",
  "startup_rotate": true, 
  "rotation": 1
}
```
Здесь, без указанных ограничений на размер и время, значения `rotation` больше единицы не дают эффекта.
Для обнуления файла при достижении заданного размера (1МБ):
```cpp
{
  "path": "/path/to/log/file.log",
  "size_limit": 1048576
}
```
В следующий конфигурации при запуске, запись будет продолжена в указанный лог, но при достижении размера 
в 1МБ файл будет переименован '/path/to/log/file.log.old-0' и запись начнется с начала файла:
```cpp
{
  "path": "/path/to/log/file.log",
  "size_limit": 1048576, 
  "rotation": 1
}
```
Запись в новый файл при запуске и сохранении истории в 10 файлов, с размером не более 1 МБ каждый: 
```cpp
{
  "path": "/path/to/log/file.log",
  "startup_rotate": true,
  "size_limit": 1048576, 
  "rotation": 10
}
```
Посуточная ротация файлов с историей за месяц:
```cpp
{
  "path": "/path/to/log/file.log",
  "time_limit": 86400, 
  "rotation": 30
}
```
Посекундные срезы (например при трассировании трафика при большой нагрузе ): 
```cpp
{
  "path": "/path/to/log/file.log",
  "startup_rotate": true,
  "time_limit": 1, 
  "rotation": 1024
}
```

### Настройки форматирования

Для отображения долей секунд используется опция `resolution` со следующими значениями: `seconds` (без долей), `deciseconds`, `centiseconds`, `milliseconds`, `microseconds` или `nanoseconds`, например:
```cpp
{
  "path": "/path/to/log/file.log",
  "resolution": "milliseconds"
}
```

#### Форматирование даты и времени 
Изменить отображение даты и времени можно с помощью дополнительных значений `resolution`: `minutes`, `hours`, `days`, `month`, `year` 
которые влияют на отображение информации также как опция `hide`. Опция `hide` позволяет скрыть несколько частей сообщения в любой комбинации. 
Таблица возможных значений поля `hide`:

| значение | что скрывает |
| -------- | ------------ |
| date     | все поле даты  |
| time     | все поле времени |
| year     | год в поле даты |
| month    | месяц в поле даты |
| weekday  | день недели в поле даты |
| days     | день месяца в поле даты|
| hours    | часы в поле времени |
| minutes  | минуты в поле времени |
| seconds  | секунды в поле времени|
| fraction | доли секунды |
| name     | имя лога |
| ident    | идентификатор сообщения |
| message  | текст сообщения |

Значения частично скрывающие поля даты и времени влияют на формат отображения этих полей. 
Частично `hide` перекрывают `resolution`. Общая рекомендация - если необходимого представления 
возможно добиться с помощью опции `resolution`, то используем ее.

Далее, для удобства, отдельно приведены таблицы для полей даты и времени.

Возможные комбинации для `hide` и аналогичные `resolution` для поля времени с примерами вывода:

<table>
  <tr> <th width="20%" >hide</th>                     <th width="20%">resolution</th>   <th>Пример отображения</th> </tr>
  <tr> <td></td>                         <td>milliseconds</td> <td>18:36:12.805</td> </tr>
  <tr> <td>fraction</td>                 <td>seconds</td>      <td>18:36:12</td> </tr>
  <tr> <td>fraction|seconds</td>         <td>minutes</td>      <td>18:36</td> </tr>
  <tr> <td>fraction|seconds|minutes</td> <td>hours</td>        <td>18h</td> </tr>
</table>

Следующий вывод можно добиться только с помощью `hide` для `resolution`==`milliseconds`:

<table>
  <tr> <th width="20%" >hide</th> <th width="20%">Пример отображения</th>  <th>Комментарий</th> </tr>
  <tr> <td> hours</td>                  <td>01m 55s.405 </td>    <td>Сомнительно. Например при поминутных слепках.</td> </tr>
  <tr> <td> hours|minutes </td>         <td>1514304173.456 </td> <td> <b> Если нужен unixtime.</b> </td> </tr>
  <tr> <td> hours|minutes|fraction</td> <td>1514304173</td>
                                        <td><b>Если нужен unixtime</b>. Но лучше <b>hide=hours|minutes и resolution=seconds</b></td></tr>
  <tr> <td> hours|minutes|seconds </td> <td>.456 </td>           <td>Бесполезно.</td> </tr>
  <tr> <td> hours|seconds </td>         <td>26m.37642 </td>
                                        <td>Сомнительно (доли минуты в resolution). Например при поминутных слепках.</td> </tr>
  <tr> <td> minutes|seconds </td>       <td>19h.1631487 </td>
                                        <td>Сомнительно (доли часа в resolution). Например при часовых слепках.</td> </tr>
</table>


Возможные комбинации для `hide` и аналогичные `resolution` для поля времени с примерами вывода:

<table>
  <tr> <th width="20%" >hide</th> <th width="20%">resolution</th>   <th>Пример отображения</th> </tr>
  <tr> <td>time</td>              <td>days</td>                     <td> 2017-12-27 </td> </tr>
  <tr> <td>time|days</td>         <td>month</td>                    <td>2017 Dec</td> </tr>
  <tr> <td>time|days|month</td>   <td>year</td>                     <td>2017</td> </tr>
</table>

Следующий вывод даты можно добиться только с помощью `hide`:

<table>
  <tr> <th width="20%" >hide</th> <th width="20%">Пример отображения</th>  <th>Комментарий</th> </tr>
  <tr> <td> year</td>                   <td>Wed Dec 27</td>    <td></td> </tr>
  <tr> <td> year|month </td>            <td>Wed 27</td> <td>  </td> </tr>
  <tr> <td> year|month|weekday</td>     <td>27</td> <td></td></tr>
  <tr> <td> month </td>                 <td>27 Wed 2017</td>           <td></td> </tr>
  <tr> <td> day </td>                   <td>2017 Dec </td><td></td> </tr>
  <tr> <td> minutes|seconds </td>       <td>19h.1631487 </td><td></td> </tr>
</table>

Пример:

```cpp
{
  "path": "/path/to/log/file.log",
  "resolution": "milliseconds", 
  "hide":"year|month|seconds"
}
Wed 27 17:53.17548 WLOG DEBUG Тестовое DEBUG сообщение №22000
Wed 27 17:53.18734 WLOG ERROR Тестовое ERROR сообщение №23000
Wed 27 17:53.19914 WLOG FATAL Тестовое FATAL сообщение №24000
```

#### Локализация даты и времени

Пример:

```cpp
{
  "path": "/path/to/log/file.log",
  "resolution": "milliseconds",
  "locale": "ru_RU.UTF-8"
}

Ср 27 дек 2017 18:03:29,864 EXAMPLE [DEBUG] Тестовое DEBUG сообщение №11000
Ср 27 дек 2017 18:03:31,144 EXAMPLE [ERROR] Тестовое ERROR сообщение №12000
Ср 27 дек 2017 18:03:32,426 EXAMPLE [FATAL] Тестовое FATAL сообщение №13000

{
  "path": "/path/to/log/file.log",
  "resolution": "milliseconds",
  "locale": "ru_RU.UTF-8"
}

Wed 27 Dec 2017 06:04:35 PM MSK.057 WLOG TRACE Тестовое TRACE сообщение №1000
Wed 27 Dec 2017 06:04:36 PM MSK.331 WLOG DEBUG Тестовое DEBUG сообщение №2000
Wed 27 Dec 2017 06:04:37 PM MSK.608 WLOG ERROR Тестовое ERROR сообщение №3000
```

Локализация не работает при использовании опции `hide`

## Настройки STDOUT

Наследует и/или переопределяет все настройки форматирования. Если опция определена в секции `stdout` то исползуется она.
Если нет, то опция из основной секции или значение по умолчанию. Исключение состовляет опция `colorized`, у которой в основной
секции по умолчанию занчение `none`, но если она не определен в секции `stdout`, то по умолчаню значение `all`. Иными словани,
по умолчанию, в основной лог запись идет без цветовой раскраски, а на экран в цвете.

```cpp
{
  "logger": {
    /* ... */
    "stdout": {
      /* Имя стандартного вывода (cout, cerr, clog)*/
      "name": "cout",
      "sync": false,
      "resolution": "seconds",
      "datetime_format": "",
      "hide": "",
      "locale": "",
      "colorized": "all",
      "color_map": {}
    },
    /* ... */
  }
}
```

## Цветовая схема

Для управление цветовой схемой используются опции `colorized`(для указания раскраски элементов записи лога) и `color_map`(для изменения цветовой схемы).
Значения `colorized`:

<table>
  <tr> <th width="20%" >colorized_flags</th> <th width="20%">resolution</th>   <th></th> </tr>
  <tr> <td> none      </td> <td> Отключить расскраску </td>
  <tr> <td> date      </td> <td> </td>
  <tr> <td> time      </td> <td> </td>
  <tr> <td> fraction  </td> <td> Доли секунды </td>
  <tr> <td> name      </td> <td> Имя лога </td>
  <tr> <td> notice    </td> <td> Тип сообщения </td>
  <tr> <td> ident     </td> <td> Тип сообщения </td>
  <tr> <td> message   </td> <td> Текст сообщения (если не задан в color_map, то в цвет ident)</td>
  <tr> <td> all       </td> <td> Включить в расскраску все элементы </td>
</table>

Для цветовой схемы, в качестве ключа исползуется имя лога, тип сообщения или одно из специальных значений:
* $all - всю строку одним цветом (например чтобы выделить ошибку)
* $date - цвет даты
* $time - цвет времени
* $fraction - доли секунды
* $name - цвет имени лога 
* $ident - цвет типа сообщения
* $message - цвет текста сообщения

Раскрашиваем вывод в красный цвет:

```cpp
{
  "logger": {
    "stdout": {
      "colorized": "all",
      "color_map":{"$all":"red"}
    }
  }
}
```



## Кастомные настройки логов

Позволяет настроить каждый лог индивидуально. Ассоциативный массив, где ключом имя лога в нижнем регистре:

```json
{
  "logger":{
      /*....*/
      "custom":{
        "debug":{
            "limit":0,
            "milliseconds":false,
            "stdout":"clog",
            "path":"./demo",
            "deny":[]
        }
      }
  }
}
```

* path - если не задан задан, то берется из основных настроек
* deny - расширяет список для типов сообщений основных настроек.
