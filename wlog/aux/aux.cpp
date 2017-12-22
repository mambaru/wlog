#include "aux.hpp"

namespace wlog{

  std::string expanse_path(const std::string& path, const std::string& name)
  {
    auto pos = path.rfind('.');
    if ( pos == std::string::npos )
      return path + name + std::string(".log");

    std::ptrdiff_t diff = static_cast<std::ptrdiff_t>(pos);
    return std::string( path.begin(), path.begin() + diff ) 
      + std::string("-") 
      + name 
      + std::string( path.begin() + diff, path.end() );
  }

}
