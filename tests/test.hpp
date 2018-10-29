#pragma once

#include <iostream>
#include <wlog/init.hpp>
inline bool test( bool expr, const std::string& file, int line)
{
  if ( !expr )
    std::cerr << "ERROR in " << file << ":" << line << std::endl;
  return expr;
}

#define TEST( X ) if ( !test( X, __FILE__, __LINE__ ) ) return __LINE__;
