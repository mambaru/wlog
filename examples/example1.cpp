#include <wlog/logger.hpp>
#include <wlog/options.hpp>
int main()
{
  wlog::options opt;
  //opt.path = "./example3.log";
  opt.stdout="cout";
  opt.limit = 1000000000;
  wlog::init_log(opt);
  WLOG_MESSAGE("Фамилия " << "Имя " << 1978 );
  abort();
  WLOG_MESSAGE("Фамилия " << "Имя " << 2000 );
  return 0;
}
