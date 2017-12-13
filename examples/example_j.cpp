#define WLOG_ENABLE_DEBUG_LOG ON
#include <wlog/logger.hpp>
#include <wlog/options.hpp>
#include <wlog/default_logger.hpp>
#include <iostream>

#define LOG_LINES 1000000

int main(int argc, char* argv[])
{
  if ( argc!=3 )
  {
    std::cout << "Usage:" << std::endl;
    std::cout << "\t" << argv[0] << " -G file-name.conf\tGenerate and write logger configurations."  << std::endl;
    std::cout << "\t" << argv[0] << " -C file-name.conf\tLoad and parse json-configuration."  << std::endl;
  }
  
  if (std::string(argv[1]) == "-G" )
  {
    
  }
  return 0;
}
