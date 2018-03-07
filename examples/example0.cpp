#define WLOG_ENABLE_DEBUG_LOG // Don't disable DEBUG and TRACE in Release 

#include <wlog/wlog.hpp>
#include <wlog/init.hpp>
  
int main()
{
  wlog::init("example.log"); 
  WLOG_MESSAGE( "Example N" << 1 << " message" )
  WLOG_WARNING( "Example N" << 1 << " warning" )
  WLOG_ERROR( "Example N" << 2 << " error" )
  WLOG_DEBUG( "Example N" << 3 << " debug" )
  WLOG_TRACE( "Example N" << 4 << " trace" )
  return 0;
}
