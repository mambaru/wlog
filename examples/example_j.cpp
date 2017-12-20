#define WLOG_ENABLE_DEBUG_LOG ON
#include <signal.h>
#include <iostream>
#include <fstream>
#include <wlogjson/logger_options_json.hpp>
#include <wlog/logging.hpp>
#include <wlog/init_log.hpp>
#include <wlog/logger_fun.hpp>
#include <wjson/json.hpp>
#include <wjson/strerror.hpp>
#include <unistd.h>

#define LOG_LINES 10000000

#define EXAMPLE_ERROR(X)    WLOG_LOG_ERROR   ( "EXAMPLE", X )
#define EXAMPLE_WARNING(X)  WLOG_LOG_WARNING ( "EXAMPLE", X )
#define EXAMPLE_MESSAGE(X)  WLOG_LOG_MESSAGE ( "EXAMPLE", X )
#define EXAMPLE_FATAL(X)    WLOG_LOG_FATAL   ( "EXAMPLE", X )
#define EXAMPLE_BEGIN(X)    WLOG_LOG_BEGIN   ( "EXAMPLE", X )
#define EXAMPLE_END(X)      WLOG_LOG_END     ( "EXAMPLE", X )
#define EXAMPLE_DEBUG(X)    WLOG_LOG_DEBUG   ( "EXAMPLE", X )
#define EXAMPLE_TRACE(X)    WLOG_LOG_TRACE   ( "EXAMPLE", X )
#define EXAMPLE_PROGRESS(X) WLOG_LOG_PROGRESS( "EXAMPLE", X )

void sig_handler(int );
void sig_handler(int )
{
  system("setterm -cursor on");
  exit(0);
}  

int main(int argc, char* argv[])
{
  if ( argc!=2 )
  {
    std::cout << "Usage:" << std::endl;
    std::cout << "\t" << argv[0] << " file-name.conf\tDemo log with conf."  << std::endl;
    std::cout << "\t" << argv[0] << " [0|1|2|3]\tGenerate json-configuration."  << std::endl;
    std::cout << "Example:" << std::endl;
    std::cout << "\t" << argv[0] << " 0 | python -mjson.tool"  << std::endl;
    std::cout << "\t" << argv[0] << " 1 > example.conf"  << std::endl;
    std::cout << "\t" << argv[0] << " example.conf"  << std::endl;
    return 0;
  }
  
  if ( std::isdigit(argv[1][0]) )
  {
    std::string json;
    wlog::logger_options lopt;
    if ( argv[1][0] == '0' )
    {
      lopt.finalize();
    }
    wlog::logger_options_json::serializer()(lopt, std::back_inserter(json));
    std::cout << json << std::endl;
    return 0;
  }
  
  std::ifstream ifs(argv[1]);
  std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
  wlog::logger_options opt;
  wjson::json_error e;
  wlog::logger_options_json::serializer()(opt, json.begin(), json.end(), &e);
  if ( e )
  {
    std::cerr << wjson::strerror::message_trace(e, json.begin(), json.end()) << std::endl;
    return 1;
  }

  signal(SIGINT, sig_handler);
  system("setterm -cursor off");

  wlog::logger_handlers hdr;
  hdr.customize["EXAMPLE"].ident = [](const std::string& ident) -> std::string
  {
    return "[" +  ident + "]";
  };
  
  wlog::init_log(opt, hdr);
  WLOG_MESSAGE("Demo progress LOG")
  WLOG_BEGIN("Progress...")
  for (int i = 0, j=0 ; i < LOG_LINES; ++i)
  {
    WLOG_PROGRESS( i << " " << std::fixed<<std::setprecision(3) << (i*100.0)/LOG_LINES << "%   ")
    usleep(1000);
    if ( i%1000==0 )
    {
           if ( j % 20 == 0)  {   WLOG_WARNING("Тестовое WARNING " << "сообщение №" << i ) }
      else if ( j % 20 == 1)  {   WLOG_TRACE("Тестовое TRACE " << "сообщение №" << i ) }
      else if ( j % 20 == 2)  {   WLOG_DEBUG("Тестовое DEBUG " << "сообщение №" << i ) }
      else if ( j % 20 == 3)  {   WLOG_ERROR("Тестовое ERROR " << "сообщение №" << i ) }
      else if ( j % 20 == 4)  {   WLOG_FATAL("Тестовое FATAL " << "сообщение №" << i ) }
      else if ( j % 20 == 5)  {   WLOG_BEGIN("Тестовое BEGIN " << "сообщение №" << i)  }
      else if ( j % 20 == 6)  {   WLOG_END("Тестовое END " << "сообщение №" << i)  }
      else if ( j % 20 == 7)  {   WLOG_MESSAGE("Тестовое MESSAGE " << "сообщение №" << i << "" );   }
      else if ( j % 20 == 8)  {   EXAMPLE_MESSAGE("Тестовое MESSAGE " << "сообщение №" << i << "" );   }
      else if ( j % 20 == 9)  {   EXAMPLE_WARNING("Тестовое WARNING " << "сообщение №" << i ) }
      else if ( j % 20 == 10)  {  EXAMPLE_TRACE("Тестовое TRACE " << "сообщение №" << i ) }
      else if ( j % 20 == 11) {   EXAMPLE_DEBUG("Тестовое DEBUG " << "сообщение №" << i ) }
      else if ( j % 20 == 12) {   EXAMPLE_ERROR("Тестовое ERROR " << "сообщение №" << i ) }
      else if ( j % 20 == 13) {   EXAMPLE_FATAL("Тестовое FATAL " << "сообщение №" << i ) }
      else if ( j % 20 == 14) {   EXAMPLE_BEGIN("Тестовое BEGIN " << "сообщение №" << i)  }
      else if ( j % 20 == 15) {   EXAMPLE_END("Тестовое END " << "сообщение №" << i)  }
      else if ( j % 20 == 16)  {  SYSLOG_INFO("Тестовое INFO " << "сообщение №" << i)  }
      else if ( j % 20 == 17)  {  SYSLOG_NOTICE("Тестовое NOTICE " << "сообщение №" << i)  }
      else if ( j % 20 == 18)  {  SYSLOG_ALERT("Тестовое ALERT " << "сообщение №" << i)  }
      else if ( j % 20 == 19)  {  SYSLOG_CRIT("Тестовое CRIT " << "сообщение №" << i)  }
      ++j;
    }
  }
  system("setterm -cursor on");
  WLOG_PROGRESS( LOG_LINES << " " << 100 << "%        " << std::endl)
  WLOG_END("Progress... Done")
  
  return 0;
}
