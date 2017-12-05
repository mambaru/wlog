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
  
  //opt.stdout = "clog";
  wlog::init_log( /*wlog::default_logger(opt)*/opt );
  for (int i = 0; i < LOG_LINES; ++i)
  {
    if ( i % 10 == 0)
    {
      WLOG_WARNING("Тестовое " << "сообщение №" << i << "" );
    }
    else if ( (i+1) % 10 == 0)
    {
      WLOG("WLOG", "TRACE", "Тестовое " << "сообщение №" << i << "" );
    }
    else if ( (i+2) % 10 == 0)
    {
      WLOG("WLOG", "DEBUG", "Тестовое " << "сообщение №" << i << "" );
    }
    else if ( (i+3) % 10 == 0)
    {
      WLOG_ERROR("Тестовое " << "сообщение №" << i << "" );
    }
    else if ( (i+4) % 10 == 0)
    {
      WLOG_FATAL("Тестовое " << "сообщение №" << i << "" );
    }
    else if ( (i+5) % 10 == 0)
    {
      WLOG_BEGIN("Тестовое " << "сообщение №" << i << "" );
    }
    else
      WLOG_MESSAGE("Тестовое " << "сообщение №" << i << "" );
  }
  return 0;
}
