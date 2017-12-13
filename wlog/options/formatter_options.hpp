//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/options/resolutions.hpp>
#include <wlog/options/hide_flags.hpp>
#include <wlog/options/colorized_flags.hpp>

#include <string>
#include <unordered_map>


namespace wlog{
 
struct formatter_options
{
  resolutions resolution = resolutions::inherited;
  hide_flags hide = hide_flags::inherited;
  colorized_flags colorized = colorized_flags::inherited;
  std::string locale;
  std::unordered_map<std::string, std::string> color_map;
};

inline formatter_options& operator <<= (formatter_options& self, const formatter_options& other)
{
  if ( self.resolution == resolutions::inherited )
    self.resolution = other.resolution;
  
  if ( self.hide == hide_flags::inherited )
    self.hide = other.hide;
  
  if ( self.colorized == colorized_flags::inherited) 
    self.colorized = other.colorized;
  
  if ( self.locale == "" )
    self.locale = other.locale;
  
  if ( self.locale == "#" )
    self.locale.clear();
    
  for (const auto& c : other.color_map)
    if ( 0 == self.color_map.count(c.first) )
      self.color_map.emplace(c);

  return self;
}

}
