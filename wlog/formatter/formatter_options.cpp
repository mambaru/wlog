//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include <wlog/formatter/formatter_options.hpp>

namespace wlog{
 
formatter_options& formatter_options::operator <<= (const formatter_options& other)
{
  formatter_options& self = *this;
  
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

void formatter_options::upgrade()
{
  // TODO: color_map
}

}
