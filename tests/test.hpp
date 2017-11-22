#include <iostream>

inline bool test( bool expr, const std::string& file, int line)
{
  if ( !expr )
    std::cerr << "ERROR in " << file << ":" << line << std::endl;
  return expr;
}
