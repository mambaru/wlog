#include <wlog/formatter/formatter.hpp>
#include "test.hpp"
#include <sstream>
#include <chrono>

namespace
{

int test1();
int test2();
int test3();

static const time_t test_time = 1512672862;
static const char* ru_date = "Чт 07 дек 2017 21:54:22";
static const char* en_date = "Thu 07 Dec 2017 09:54:22 PM MSK";
static wlog::time_point tp;

int test1()
{
  std::stringstream ss;
  wlog::formatter_options opt;
  wlog::formatter_handlers hdr;
  opt.colorized = wlog::colorized_flags::date;
  wlog::formatter::date(ss, tp, opt, hdr);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == "\033[32m2017-12-07\033[0m"  );
 
  ss.str(""); ss.clear();

  opt.locale="en_US.UTF-8";
  opt.colorized = wlog::colorized_flags::none;
  wlog::formatter::date(ss, tp, opt, hdr);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == en_date );
 
  ss.str(""); ss.clear();
  opt.locale="ru_RU.UTF-8";
  wlog::formatter::date(ss, tp, opt, hdr);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == ru_date );
  
  ss.str(""); ss.clear();
  opt.locale="ru_RU.UTF-8";
  opt.hide = wlog::hide_flags::year;
  opt.resolution = wlog::resolutions::month;
  wlog::formatter::date(ss, tp, opt, hdr);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == "дек" );
  
  ss.str(""); ss.clear();
  opt.locale="ru_RU.UTF-8";
  opt.hide = wlog::hide_flags::none;
  opt.resolution = wlog::resolutions::year;
  wlog::formatter::date(ss, tp, opt, hdr);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == "2017" );
  
  return 0;
}

int test2()
{
  std::stringstream ss;
  wlog::formatter_options opt;
  wlog::formatter_handlers hdr;
  wlog::formatter::time(ss, tp, opt, hdr);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == "21:54:22"  );
  
  ss.str(""); ss.clear();
  opt.locale="en_US.UTF-8";
  wlog::formatter::time(ss, tp, opt, hdr);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == "09:54:22 PM"  );

  ss.str(""); ss.clear();
  opt.locale.clear();//="ru_RU.UTF-8";
  opt.hide = wlog::hide_flags::hours;
  opt.resolution = wlog::resolutions::minutes;
  wlog::formatter::time(ss, tp, opt, hdr);
  std::cout << "[" << ss.str() << "]" << std::endl;
  TEST( ss.str() == "54m" );
  
  return 0;
}

int test3()
{
  std::stringstream ss;
  wlog::formatter_options opt;
  wlog::formatter_handlers hdr;
  opt.locale="ru_RU.UTF-8";
  opt.colorized = wlog::colorized_flags::none;
  opt.resolution = wlog::resolutions::deciseconds;
  wlog::formatter::fraction(ss, tp, opt, hdr);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == ".1" );
  
  ss.str(""); ss.clear();
  opt.resolution = wlog::resolutions::centiseconds;
  wlog::formatter::fraction(ss, tp, opt, hdr);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == ".12" );
  
  ss.str(""); ss.clear();
  opt.resolution = wlog::resolutions::milliseconds;
  wlog::formatter::fraction(ss, tp, opt, hdr);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == ".123" );

  ss.str(""); ss.clear();
  opt.resolution = wlog::resolutions::microseconds;
  wlog::formatter::fraction(ss, tp, opt, hdr);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == ".123456" );

  ss.str(""); ss.clear();
  opt.resolution = wlog::resolutions::nanoseconds;
  wlog::formatter::fraction(ss, tp, opt, hdr);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == ".123456789" );
  
  return 0;
}

int test4()
{
  wlog::formatter_handlers hdr;
  wlog::formatter_options opt;
  opt.resolution = wlog::resolutions::microseconds;
  opt.colorized = wlog::colorized_flags::none;
  
  {
    std::stringstream ss;
    wlog::formatter fmt(opt, wlog::formatter_handlers() );
    fmt(ss, tp, "hello", "world", "!");
    std::cout << "[" << ss.str() << "]" << std::endl;
    std::string str1="2017-12-07 21:54:22.123456 hello world !";
    std::string str2=ss.str();
    TEST( str1 == str2 );
   
  }
  
  opt.resolution = wlog::resolutions::seconds;
  {
    std::stringstream ss;
    wlog::formatter fmt(opt, wlog::formatter_handlers());
    fmt(ss, tp, "hello", "world", "!");
    std::cout << ss.str() << std::endl;
    TEST( ss.str() == "2017-12-07 21:54:22 hello world !" );
  }

  opt.resolution = wlog::resolutions::minutes;
  opt.hide = wlog::hide_flags::year;
  {
    std::stringstream ss;
    wlog::formatter fmt(opt, wlog::formatter_handlers());
    fmt(ss, tp, "hello", "world", "!");
    std::cout << ss.str() << std::endl;
    TEST( ss.str() == "Thu Dec 07 21:54 hello world !" );
  }

  opt.resolution = wlog::resolutions::minutes;
  opt.hide = wlog::hide_flags::year | wlog::hide_flags::weekday;
  {
    std::stringstream ss;
    wlog::formatter fmt(opt, wlog::formatter_handlers());
    fmt(ss, tp, "hello", "world", "!");
    std::cout << ss.str() << std::endl;
    TEST( ss.str() == "Dec 07 21:54 hello world !" );
  }

  opt.resolution = wlog::resolutions::minutes;
  opt.colorized = wlog::colorized_flags::name | wlog::colorized_flags::ident | /*wlog::colorized_flags::message |*/ wlog::colorized_flags::time;
  //opt.color_map["hello1"] = "\033[94m";
  opt.hide = wlog::hide_flags::year | wlog::hide_flags::weekday;
  {
    std::stringstream ss;
    wlog::formatter fmt(opt, wlog::formatter_handlers());
    fmt(ss, tp, "hello", "world", "!");
    std::cout << ss.str() << std::endl;
    //TEST( ss.str() == "Dec 07 21:54 hello world !" );
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
  if ( int res = test2() )
    return res;
  if ( int res = test3() )
    return res;
  if ( int res = test4() )
    return res;
  
  return 0;  
}
