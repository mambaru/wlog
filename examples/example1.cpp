#define WLOG_ENABLE_DEBUG_LOG

#include <wlog/wlog.hpp>
#include <iomanip>
#include <unistd.h>
  
static const int TOTAL = 10000;

#define WLOG_DEBUG_IF(A, X) if (A) WLOG_DEBUG(X)

int main()
{
  WLOG_MESSAGE("Message before init_log()")
  WCOUT("std::cout << " << "Message before init_log()")
  wlog::init_log();
  WLOG_MESSAGE("Demo progress LOG")
  WLOG_BEGIN("Progress...")
  for (int i = 0 ; i < TOTAL; ++i)
  {
    WLOG_PROGRESS( i << " " << std::fixed<<std::setprecision(2) << (i*100.0)/TOTAL << "%   ")
    WLOG_DEBUG_IF( i%1000==0 && i!=0, "intermediate result " << i << "                         ")
    /*if ( i % 1000 == 0 && i != 0)
    {
      WLOG_DEBUG( "intermediate result " << i << "                         ")
    }*/
    usleep(1000);
  }
 
  WLOG_PROGRESS( TOTAL << " " << 100 << "%        " << std::endl)
  WLOG_END("Progress... Done")
  
  //std::cout << x << std::endl;
  return 0;
}
