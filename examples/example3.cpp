#include <wlog/logger.hpp>
#include <wlog/options.hpp>
#include <wlog/default_logger.hpp>
#define LOG_LINES 1000000
int main()
{
  wlog::options opt;
  opt.path = "./example3.log";
  opt.stdout.clear();
  opt.limit = 1000000;
  //opt.save_old = 3;
  wlog::init_log( wlog::default_logger(opt));
  for (int i = 0; i < LOG_LINES; ++i)
    WLOG_MESSAGE("Фамилия " << "Имя " << 1978 );
  return 0;
}
