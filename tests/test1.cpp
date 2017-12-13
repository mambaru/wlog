#include <wlog/logstream.hpp>
#include "test.hpp"

int test1();
int test2();



int test1()
{
  std::mutex m;
  std::string message;
  {
    wlog::logstream log(m, "test", "message", 
      [&message](const wlog::time_point&, const std::string& name, const std::string& ident, const std::string& text)
      {
        std::cout << name << "," << ident << "," << text << " >> " << message << std::endl;
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
  std::cout << message << std::endl;
  TEST( message=="testmessagehello 12" );
  return 0;
}

int test2()
{
  std::string message;
  {
    std::mutex m;
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
  /*
  char x[10]={0};
  int num = std::atoi(argv[1]);
  for (int i =0; i < num; ++i)
    x[i]='a' + i;
  std::cout << x << std::endl;
  */
  if ( int res = test1() )
    return res;
  if ( int res = test2() )
    return res;
  return 0;  
}
