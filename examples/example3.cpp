#define WLOG_ENABLE_DEBUG_LOG ON
#include <wlog/logger.hpp>
#include <wlog/options.hpp>
#include <wlog/default_logger.hpp>
#include <iostream>
#define LOG_LINES 1000000
int main(int argc, char* argv[])
{
  //
  wlog::options opt;
  opt.path = "./example3.log";
  opt.stdout.clear();
  if ( argc > 1 )
    opt.sync = atoi(argv[1])!=0;

  if ( argc > 2 )
    opt.save_old = atoi(argv[2]);

  if ( argc > 3 )
    opt.limit = atol(argv[3]);
  
  std::cout << argv[0] << " " << opt.sync << " " << opt.save_old << " " << opt.limit<< std::endl;
  
  wlog::init_log( opt );
  for (int i = 0; i < LOG_LINES; ++i)
  {
    if ( i % 10 == 0 )
      { WLOG_WARNING("Тестовое " << "сообщение №" << i ) }
    else if ( i % 10 == 1)
      {   WLOG_TRACE("Тестовое " << "сообщение №" << i ) }
    else if ( i % 10 == 2)
      {   WLOG_DEBUG("Тестовое " << "сообщение №" << i ) }
    else if ( i % 10 == 3)
      {   WLOG_ERROR("Тестовое " << "сообщение №" << i ) }
    else if ( i % 10 == 4)
      {   WLOG_FATAL("Тестовое " << "сообщение №" << i ) }
    else if ( i % 10 == 5)
      {   WLOG_BEGIN("Тестовое " << "сообщение №" << i)  }
    else if ( i % 10 == 6)
      {   WLOG_END("Тестовое " << "сообщение №" << i)  }
    else if ( i % 10 == 7)
      {   WLOG_PROGRESS("Тестовое " << "сообщение №" << i << std::endl)  }
    else
      WLOG_MESSAGE("Тестовое " << "сообщение №" << i << "" );
  }
  return 0;
}