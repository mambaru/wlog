//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/formatter/resolutions.hpp>
#include <wlog/formatter/hide_flags.hpp>
#include <wlog/formatter/colorized_flags.hpp>

#include <string>
#include <map>


namespace wlog{
 
struct formatter_options
{
  int name_width = -1;
  int ident_width = -1;
  resolutions resolution = resolutions::inherited;
  colorized_flags colorized = colorized_flags::inherited;
  hide_flags hide = hide_flags::inherited;
  
  std::string locale;
  std::string datetime_format; // date format : TODO
  
  std::map<std::string, std::string> color_map; //TODO
  
  void upgrade(const formatter_options& other);
  void finalize();

};


}
