#include <wlog/global_log.hpp>
#include <wlog/logger.hpp>
#include <wlog/options.hpp>
#include <wlog/default_logger.hpp>
#include "test.hpp"

int test1();
int test2();
int test3();

int test1()
{
  wlog::options opt;
  opt.deny.insert("WARNING");
  opt.deny.insert("MYLOG2");
  opt.path = "./test3.log";
  opt.customize["MYLOG"].milliseconds = true;
  wlog::init_log( wlog::default_logger(opt) );
  WLOG_MESSAGE("Привет MESSAGE");
  WLOG_WARNING("Привет WARNING");
  WLOG_LOG_FATAL("MYLOG", "Привет FATAL");
  WLOG_LOG_WARNING("MYLOG", "Привет WARNING");
  WLOG_LOG_MESSAGE("MYLOG2", "Привет MESSAGE");
  return 0;
}

int test2()
{
  return 0;
}

int test3()
{
  return 0;
}

int main()
{
  if ( int res = test1() )
    return res;
  if ( int res = test2() )
    return res;
  if ( int res = test3() )
    return res;
  return 0;  
}
