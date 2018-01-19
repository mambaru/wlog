#include <wlog/formatter/formatter.hpp>
#include <wlog/writer/file_writer.hpp>
#include <iostream> 
#include "test.hpp"

namespace 
{
  
static const time_t test_time = 1512672862;
static wlog::time_point tp;

int test1();

int test1()
{
  {
    wlog::file_writer::options opt;
    opt.startup_rotate = 1;
    opt.path = "./test4.log";
    wlog::formatter_options fo;
    wlog::formatter fmt(fo, wlog::formatter_handlers() );
    wlog::file_writer fw( fmt, opt);
    fw(tp, "TEST4", "MESSAGE", "test1\n");
    std::ifstream ifs("./test4.log");
    std::string testline;
    std::getline( ifs, testline);
    std::cout << "[" << testline << "]" << std::endl;
    TEST( testline == "2017-12-07 21:54:22 TEST4  MESSAGE   test1" );
  }
  
  {
    wlog::file_writer::options opt;
    opt.startup_rotate = 1;
    opt.rotation = 1;
    opt.path = "./test4.log";
    wlog::formatter_options fo;
    wlog::formatter fmt(fo, wlog::formatter_handlers());
    wlog::file_writer fw( fmt, opt);
    fw(tp, "TEST4", "MESSAGE", "test1\n");
    {
      std::ifstream ifs("./test4.log.old-0");
      std::string testline;
      std::getline( ifs, testline);
      std::cout << "[" << testline << "]" << std::endl;
      TEST( testline == "2017-12-07 21:54:22 TEST4  MESSAGE   test1" );
    }
    
    {
      std::ifstream ifs("./test4.log");
      std::string testline;
      std::getline( ifs, testline);
      std::cout << testline << std::endl;
      TEST( testline == "2017-12-07 21:54:22 TEST4  MESSAGE   test1" );
    }
  }
  return 0;
}

}

int main()
{
  setenv("TZ", "MSK-3", 1);
  tzset();
  tp = wlog::time_point::clock::from_time_t(test_time);
  tp += std::chrono::nanoseconds(123456789);

  
  if ( int res = test1() )
    return res;
  /*if ( int res = test2() )
    return res;
  if ( int res = test3() )
    return res;*/
  return 0;  
}
