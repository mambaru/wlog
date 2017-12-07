#include <wlog/formatter.hpp>
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
  opt.colorized = wlog::colorized_flags::date;
  wlog::formatter::date(ss, tp, opt);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == "\033[32m2017-12-07\033[0m"  );
 
  ss.str(""); ss.clear();

  opt.locale="en_US.UTF-8";
  opt.colorized = wlog::colorized_flags::none;
  wlog::formatter::date(ss, tp, opt);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == en_date );
 
  ss.str(""); ss.clear();
  opt.locale="ru_RU.UTF-8";
  wlog::formatter::date(ss, tp, opt);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == ru_date );
  
  ss.str(""); ss.clear();
  opt.locale="ru_RU.UTF-8";
  opt.hide = wlog::hide_flags::year;
  opt.resolution = wlog::resolutions::month;
  wlog::formatter::date(ss, tp, opt);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == "дек" );
  
  ss.str(""); ss.clear();
  opt.locale="ru_RU.UTF-8";
  opt.hide = wlog::hide_flags::none;
  opt.resolution = wlog::resolutions::year;
  wlog::formatter::date(ss, tp, opt);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == "2017" );
  
  return 0;
}

int test2()
{
  std::stringstream ss;
  wlog::formatter_options opt;
  wlog::formatter::time(ss, tp, opt);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == "21:54:22"  );
  
  ss.str(""); ss.clear();
  opt.locale="en_US.UTF-8";
  wlog::formatter::time(ss, tp, opt);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == "09:54:22 PM"  );

  ss.str(""); ss.clear();
  opt.locale.clear();//="ru_RU.UTF-8";
  opt.hide = wlog::hide_flags::hours;
  opt.resolution = wlog::resolutions::minutes;
  wlog::formatter::time(ss, tp, opt);
  std::cout << ss.str() << std::endl;
  TEST( ss.str() == "54" );
  
  return 0;
}

int test3()
{
  std::stringstream ss;
  //ss.imbue(std::locale("ru_RU.UTF-8"));

  wlog::formatter_options opt;
  opt.locale="ru_RU.UTF-8";
  opt.colorized = wlog::colorized_flags::all;
  opt.resolution = wlog::resolutions::deciseconds;
  
  //opt.color_map["$time"]="\033[93m";
  
  /*opt.resolution = wlog::resolutions_flags::days;
  opt.hide = wlog::hide_flags::month;*/
  
  wlog::formatter::fraction(ss, tp, opt);
  std::cout << ss.str() << std::endl;
  return 0;
  return 0;
}

}

int main()
{
  setenv("TZ", "MSK-3", 1);
  tzset();

  tp = wlog::time_point::clock::from_time_t(test_time);

  if ( int res = test1() )
    return res;
  if ( int res = test2() )
    return res;
  /*if ( int res = test3() )
    return res;
  */
  return 0;  
}
