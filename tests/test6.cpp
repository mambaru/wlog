#include <wlog/wlog.hpp>
#include <wlog/load.hpp>
#include <wjson/wjson.hpp>

#define TEST_LOG_TEST0(msg) WLOG_LOG_MESSAGE("TEST0", msg)
#define TEST_LOG_TEST1(msg) WLOG_LOG_MESSAGE("TEST1", msg)
#define TEST_LOG_TEST2(msg) WLOG_LOG_ERROR("TEST2", msg)

using namespace wjson::literals;
const std::string conf_json="{\
    'startup_rotate':true, \
    'path':'./test0.log', \
    'customize':[{\
      'names':['TEST1','ERROR'],\
      'path':'./test1.log' \
    }]\
  }"_json;

int main(int , char* [])
{
  std::string er;
  wlog::init(wlog::load(conf_json, &er));
  if ( !er.empty() )
    return 1;
  TEST_LOG_TEST0("test0")
  TEST_LOG_TEST1("test1")
  TEST_LOG_TEST2("test2")
  return 0;
}
