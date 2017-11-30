#include <wlog/logstream.hpp>
#include "test.hpp"

int test1();
int test2();



int test1()
{
  std::string message;
  wlog::logstream log("test", "message", 
    [&message](std::string name, std::string type, std::string text)
    {
      message = name + type + text;
      return true;
    }
  );
  if ( !test( log.str().empty(), __FILE__, __LINE__ ) )
    return __LINE__;
  
  log << "hello " << 1;
  log << 2;

  if ( !test( !log.str().empty(), __FILE__, __LINE__ ) )
    return __LINE__;
  
  if ( !test( log.str()=="hello 12", __FILE__, __LINE__ ) )
    return __LINE__;
  
  log.write();
  
  if ( !test( !log.str().empty(), __FILE__, __LINE__ ) )
    return __LINE__;
  
  if ( !test( message=="testmessagehello 12", __FILE__, __LINE__ ) )
    return __LINE__;
  
  return 0;
}

int test2()
{
  std::string message;
  {
    wlog::logstream log("test", "message", 
      [&message](std::string name, std::string type, std::string text)
      {
        message = name + type + text;
        return true;
      }
    );

    log << "hello " << 1;
    log << 2;
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
