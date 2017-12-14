#define WLOG_ENABLE_DEBUG_LOG ON
#include <wlog/logging.hpp>
#include <wlog/init_log.hpp>
#include <wlog/logger/logger_options.hpp>
#include <wlog/logger/default_logger.hpp>
#include <iostream>

#define LOG_LINES 1000000

int main(int, char* [])
{
  //
  wlog::logger_options opt;
  opt.path = "./example2.log";
  opt.colorized = wlog::full_color;
  opt.resolution = wlog::resolutions::centiseconds;
  opt.rotation = 10;
  opt.size_limit = 1024*1024*100;
  opt.time_limit = 1;
  opt.hide = wlog::hide_flags::name | wlog::hide_flags::ident | wlog::hide_flags::date | wlog::hide_flags::hours;
  //opt.stdout.colorized = wlog::full_color;
  opt.stdout.name = "cout";
  //opt.upgrade();
  wlog::init_log( opt );
  for (int i = 0; i < LOG_LINES; ++i)
  {
    if ( i % 10 == 0 )
      { WLOG_WARNING("Тестовое WARNING " << "сообщение №" << i ) }
    else if ( i % 10 == 1)
      {   WLOG_TRACE("Тестовое TRACE " << "сообщение №" << i ) }
    else if ( i % 10 == 2)
      {   WLOG_DEBUG("Тестовое DEBUG " << "сообщение №" << i ) }
    else if ( i % 10 == 3)
      {   WLOG_ERROR("Тестовое ERROR " << "сообщение №" << i ) }
    else if ( i % 10 == 4)
      {   WLOG_FATAL("Тестовое FATAL " << "сообщение №" << i ) }
    else if ( i % 10 == 5)
      {   WLOG_BEGIN("Тестовое BEGIN " << "сообщение №" << i)  }
    else if ( i % 10 == 6)
      {   WLOG_END("Тестовое END " << "сообщение №" << i)  }
    else if ( i % 10 == 7)
      {   WLOG_PROGRESS("Тестовое PROGRESS " << "сообщение №" << i << std::endl)  }
    else
      WLOG_MESSAGE("Тестовое MESSAGE " << "сообщение №" << i << "" );
  }
  return 0;
}
