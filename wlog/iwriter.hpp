#pragma once
#include <string>

namespace wlog{
  
struct iwriter
{
  virtual ~iwriter(){}
  virtual void write(const std::string& str) = 0;
};

}
