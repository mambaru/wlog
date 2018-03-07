
#include <wlog/log.hpp>
#include <wlog/init.hpp> 

int main()
{
  wlog::init("Hello.txt");
  WLOG_MESSAGE("Hello log!")
  WLOG_MESSAGE("Hello log!")
  WLOG_MESSAGE("Hello log!")
  return 0;
}
