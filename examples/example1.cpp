#define WLOG_ENABLE_DEBUG_LOG ON
#include <wlog/logger.hpp>
#include <wlog/options.hpp>
#include <unistd.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <chrono>
  
static const int TOTAL = 10000;
int main()
{
  wlog::init_log();
  WLOG_BEGIN("example1")
  for (int i = 0 ; i < TOTAL; ++i)
  {
    WLOG_PROGRESS( i << " " << std::fixed<<std::setprecision(2) << (i*100.0)/TOTAL << "%   ")
    if ( i % 10 == 0 )
    {
      WLOG_DEBUG( i << "                         ")
    }
    usleep(1000);
  }
 
  WLOG_PROGRESS( 100 << "%        " << std::endl)
  WLOG_END("DONE")
  
  //std::cout << x << std::endl;
  return 0;
}
