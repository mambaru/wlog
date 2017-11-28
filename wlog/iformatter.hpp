#pragma once
#include <string>

namespace wlog{
  
struct iformatter
{
  virtual ~iformatter(){}
  virtual std::string format(const std::string& name, const std::string& ident, const std::string& str) = 0;
};

}
