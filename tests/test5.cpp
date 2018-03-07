#include <wlog/init.hpp>
#include <wlog/load.hpp>
#include <iostream>
 
int main(int argc, char* argv[])
{
  std::string jsonsrc;
  wlog::logger_options options;
  if ( argc == 1 )
  {
    wlog::custom_logger_options custom;
    custom.names.push_back("FATAL");
    custom.names.push_back("ERROR");
    options.customize.push_back(custom);
    options.finalize();
    jsonsrc = wlog::dump(options);
    std::cout << jsonsrc << std::endl;
    options = wlog::logger_options();
  }
  else
  {
    jsonsrc = argv[1];
  }
  
  if ( !wlog::load(jsonsrc, &options, nullptr) )
    return 1;
  
  return 0;  
}
