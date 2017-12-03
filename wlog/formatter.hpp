//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>
#include <set>

namespace wlog{

class formatter
{
public:
  formatter(bool milliseconds, const std::set< std::string >& deny, const std::set< std::string >& allow);
  std::string operator()(const std::string& name, const std::string& ident, const std::string& str) const;
private:
  bool is_deny_(const std::string& some) const;
private:
  const bool _milliseconds;
  const std::set< std::string > _deny;
  const std::set< std::string > _allow;
};

}
