#include <wlog/formatter.hpp>
#include <wlog/file_writer.hpp>
#include "test.hpp"

namespace 
{
  
static const time_t test_time = 1512672862;
static wlog::time_point tp;

int test1();



int test1()
{
  wlog::file_writer::options opt;
  opt.path = "./test4.log";
  wlog::formatter_options fo;
  /*fo.hide = wlog::hide_flags::none;
  fo.resolution = wlog::resolutions::nanoseconds;*/
  wlog::formatter fmt(fo);
  wlog::file_writer fw( fmt, opt);
  fw(tp, "TEST4", "MESSAGE", "test1\n");
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
