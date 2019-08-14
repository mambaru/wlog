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
    custom.path="$";
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

  if ( options.get_customize("UNKNOWN") != nullptr )
    return 2;

  if ( auto pcustom = options.get_customize("FATAL") )
  {
    if ( pcustom->names.size() != 1 )
      return 4;

    if ( pcustom->names[0]!="FATAL" )
      return 5;
  }
  else
    return 3;

  return 0;
}
