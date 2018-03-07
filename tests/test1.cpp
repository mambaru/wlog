#include <wlog/logstream.hpp>
#include <wlog/logging.hpp>
#include "test.hpp"

int test1();
int test2();

int test1()
{
  wlog::mutex_type m;
  std::string message;
  {
    wlog::logstream log(m, "test", "message", 
      [&message](const wlog::time_point&, const std::string& name, const std::string& ident, const std::string& text)
      {
        WCOUT( name << "," << ident << "," << text << " >> " << message << std::endl );
        message = name + ident + text;
        std::cout << "<<" << message << std::endl;
        return true;
      }
    );

    TEST( log.str().empty() );
    log.log() << "hello " << 1;
    log.log() << 2;
    TEST( !log.str().empty() );
    TEST( log.str()=="hello 12" );
  }
  WCOUT( message << std::endl )
  WCLOG( "WCLOG" )
  WCERR( "WCERR" )
  TEST( message=="testmessagehello 12" );
  return 0;
}

int test2()
{
  std::string message;
  {
    wlog::mutex_type m;
    wlog::logstream log(m, "test", "message", 
      [&message](wlog::time_point, std::string name, std::string type, std::string text)
      {
        message = name + type + text;
        return true;
      }
    );

    log.log() << "hello " << 1;
    log.log() << 2;
  }

  if ( !test( message=="testmessagehello 12", __FILE__, __LINE__ ) )
    return __LINE__;
  
  return 0;
}
int main(int , char* [])
{
  if ( int res = test1() )
    return res;
  if ( int res = test2() )
    return res;
  return 0;  
}
