//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/iformatter.hpp>
#include <string>
#include <set>

namespace wlog{

class formatter
  //: public iformatter
{
public:
  formatter(bool milliseconds, const std::set< std::string >& deny);
  std::string format(const std::string& name, const std::string& ident, const std::string& str);
private:
  bool is_deny_(const std::string& some) const;
private:
  bool _milliseconds;
  std::set< std::string > _deny;
};

}
