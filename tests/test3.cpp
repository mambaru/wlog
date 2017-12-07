#include <wlog/formatter.hpp>
#include "test.hpp"
#include <sstream>
#include <chrono>

int test1();
int test2();
int test3();

static wlog::time_point tp = wlog::time_point::clock::now();

int test1()
{
  std::stringstream ss;
  //ss.imbue(std::locale("ru_RU.UTF-8"));

  wlog::formatter_options opt;
  //opt.locale="ru_RU.UTF-8";
  opt.colorized = wlog::colorized_flags::all;
  opt.color_map["$date"]="\033[93m";
  
  /*opt.resolution = wlog::resolutions_flags::days;
  opt.hide = wlog::hide_flags::month;*/
  
  wlog::formatter::date(ss, tp, opt);
  std::cout << ss.str() << std::endl;
  return 0;
}

int test2()
{
  std::stringstream ss;
  //ss.imbue(std::locale("ru_RU.UTF-8"));

  wlog::formatter_options opt;
  opt.locale="ru_RU.UTF-8";
  opt.colorized = wlog::colorized_flags::all;
  //opt.color_map["$time"]="\033[93m";
  
  /*opt.resolution = wlog::resolutions_flags::days;
  opt.hide = wlog::hide_flags::month;*/
  
  wlog::formatter::time(ss, tp, opt);
  std::cout << ss.str() << std::endl;
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
