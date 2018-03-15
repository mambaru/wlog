#define WLOG_ENABLE_DEBUG_LOG ON
#include <signal.h>
#include <iostream>
#include <fstream>
#include <wlog/logging.hpp>
#include <wlog/init.hpp>
#include <wlog/load.hpp>
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
void sig_handler(int sig)
{
  if ( -1 == system("setterm -cursor on") )
    abort();
  if ( sig == SIGINT )
    exit(0);
  return;
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
  
  wlog::logger_options opt;
  
  if ( std::isdigit(argv[1][0]) )
  {
    if ( argv[1][0] == '0' )
    {
      opt.finalize();
    }
    std::cout << wlog::dump(opt) << std::endl;
    return 0;
  }
  
  
  std::string er;
  if ( !wlog::load(argv[1], &opt, &er) )
  {
    std::cerr << er << std::endl;
  }

  signal(SIGINT, sig_handler);
  if ( -1 == system("setterm -cursor off") )
    abort();

  wlog::logger_handlers hdr;
  hdr.customize["EXAMPLE"].ident = [](const std::string& ident) -> std::string
  {
    return "[" +  ident + "]";
  };
  
  wlog::init(opt, hdr);
  WLOG_MESSAGE("Demo progress LOG")
  WLOG_BEGIN("Progress...")
  for (int i = 0, j=0 ; i < LOG_LINES; ++i)
  {
    WLOG_PROGRESS( i << " " << std::fixed<<std::setprecision(3) << (i*100.0)/LOG_LINES << "%   ")
    usleep(1000);
    if ( i%1000==0 )
    {
           if ( j % 20 == 0)  { WLOG_WARNING("Test WARNING " << "message №" << i )            }
      else if ( j % 20 == 1)  { WLOG_TRACE("Test TRACE " << "message №" << i )                }
      else if ( j % 20 == 2)  { WLOG_DEBUG("Test DEBUG " << "message №" << i )                }
      else if ( j % 20 == 3)  { WLOG_ERROR("Test ERROR " << "message №" << i )                }
      else if ( j % 20 == 4)  { WLOG_FATAL("Test FATAL " << "message №" << i )                }
      else if ( j % 20 == 5)  { WLOG_BEGIN("Test BEGIN " << "message №" << i)                 }
      else if ( j % 20 == 6)  { WLOG_END("Test END " << "message №" << i)                     }
      else if ( j % 20 == 7)  { WLOG_MESSAGE("Test MESSAGE " << "message №" << i << "" )      }
      else if ( j % 20 == 8)  { EXAMPLE_MESSAGE("Test MESSAGE " << "message №" << i << "")    }
      else if ( j % 20 == 9)  { EXAMPLE_WARNING("Test WARNING " << "message №" << i )         }
      else if ( j % 20 == 10) { EXAMPLE_TRACE("Test TRACE " << "message №" << i )             }
      else if ( j % 20 == 11) { EXAMPLE_DEBUG("Test DEBUG " << "message №" << i )             }
      else if ( j % 20 == 12) { EXAMPLE_ERROR("Test ERROR " << "message №" << i )             }
      else if ( j % 20 == 13) { EXAMPLE_FATAL("Test FATAL " << "message №" << i )             }
      else if ( j % 20 == 14) { EXAMPLE_BEGIN("Test BEGIN " << "message №" << i)              }
      else if ( j % 20 == 15) { EXAMPLE_END("Test END " << "message №" << i)                  }
      else if ( j % 20 == 16) { WSYSLOG_INFO("Test INFO " << "message №" << i)                 }
      else if ( j % 20 == 17) { WSYSLOG_NOTICE("Test NOTICE " << "message №" << i)             }
      else if ( j % 20 == 18) { WSYSLOG_ALERT("Test ALERT " << "message №" << i)               }
      else if ( j % 20 == 19) { WSYSLOG_CRIT("Test CRIT " << "message №" << i)                 }
      ++j;
    }
  }
  if ( -1 == system("setterm -cursor on") )
    abort();
  WLOG_PROGRESS( LOG_LINES << " " << 100 << "%        " << std::endl)
  WLOG_END("Progress... Done")
  
  return 0;
}
