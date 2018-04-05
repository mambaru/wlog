//#include <wlog/global_log.hpp>
#include <wlog/init.hpp>
#include <wlog/logging.hpp>
#include "test.hpp"

int test1();
int test2();
int test3();

int test1()
{
  std::string message;
  wlog::init(
    [&message](wlog::time_point, std::string name, std::string type, std::string text)
    {
      message = name + type + text;
      return true;
    }
  );
  
  wlog::global_log("test", "message").log() << "hello " << 1 << 2;

  if ( !test( message=="testmessagehello 12", __FILE__, __LINE__ ) )
    return __LINE__;
  
  return 0;
}

int test2()
{
  std::string message;
  wlog::init();
  
  wlog::global_log("test", "message").log() << "hello " << 1 << 2;

  if ( !test( message=="", __FILE__, __LINE__ ) )
    return __LINE__;

  std::clog << std::endl;
  return 0;
}

int test3()
{
  std::string message;
  wlog::init(
    [&message](wlog::time_point, std::string name, std::string type, std::string text)
    {
      message += name + type + text;
      return true;
    }
  );

  WLOG_MESSAGE(1)
  WLOG_WARNING(2)
  WLOG_ERROR(3)
  WLOG_FATAL(4)
  WLOG_BEGIN(5)
  WLOG_END(6)
  WLOG_DEBUG(7)
  WLOG_TRACE(8)

#ifndef NDEBUG
  std::string checkmsg="WLOGMESSAGE1\nWLOGWARNING2\nWLOGERROR3\nWLOGFATAL4\nWLOGBEGIN5\nWLOGEND6\nWLOGDEBUG7\nWLOGTRACE8\n";
#else  
  std::string checkmsg="WLOGMESSAGE1\nWLOGWARNING2\nWLOGERROR3\nWLOGFATAL4\nWLOGBEGIN5\nWLOGEND6\n";
#endif
  if ( !test( message==checkmsg, __FILE__, __LINE__ ) )
    return __LINE__;
  
  message.clear();
  WLOG_PROGRESS(9)
  checkmsg="WLOGPROGRESS9\r";
  if ( !test( message==checkmsg, __FILE__, __LINE__ ) )
    return __LINE__;
  
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
