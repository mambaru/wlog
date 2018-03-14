
#include <wlog/log.hpp>
#include <wlog/init.hpp> 

int main()
{
  wlog::init("Hello.log");
  WLOG_MESSAGE("Hello " << "log!")
  WLOG_WARNING("Hello " << "log!")
  WLOG_ERROR("Hello " << "log!")
  WLOG_DEBUG("Hello " << "log!")
  WLOG_TRACE("Hello " << "log!")
  return 0;
}
