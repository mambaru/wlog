#define WLOG_ENABLE_DEBUG_LOG ON
#include <iostream>
#include <wlogjson/logger_options_json.hpp>

#define LOG_LINES 1000000

int main(int argc, char* argv[])
{
  if ( argc!=3 )
  {
    std::cout << "Usage:" << std::endl;
    std::cout << "\t" << argv[0] << " -G file-name.conf\tGenerate and write logger configurations."  << std::endl;
    std::cout << "\t" << argv[0] << " -C file-name.conf\tLoad and parse json-configuration."  << std::endl;
    return 0;
  }
  
  if (std::string(argv[1]) == "-G" )
  {
    wlog::logger_options lopt;
    lopt.upgrade();
    //lopt.stdout.colorized = wlog::colorized_flags::date | wlog::colorized_flags::time;
    //lopt.colorized = wlog::colorized_flags::all;
    //lopt.colorized = wlog::colorized_flags::all;
    std::string json;
    wlog::logger_options_json::serializer()(lopt, std::back_inserter(json));
    std::cout << json << std::endl;
  }
  return 0;
}
