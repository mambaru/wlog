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
  this->color_map.emplace("WARNING", "\033[93m");
  this->color_map.emplace("ERROR",   "\033[91m");
  this->color_map.emplace("FATAL",   "\033[31m");
  this->color_map.emplace("EMERG",   "\033[31m");
  this->color_map.emplace("CRIT",    "\033[31m");
  this->color_map.emplace("ALERT",   "\033[31m");
  
  if ( bool( this->colorized & colorized_flags::ident) )
  {
    this->color_map.emplace("MESSAGE",  "\033[97m");
    this->color_map.emplace("INFO",     "\033[97m");
    this->color_map.emplace("TRACE",    "\033[90m");
    this->color_map.emplace("DEBUG",    "\033[33m");
    this->color_map.emplace("BEGIN",    "\033[96m");
    this->color_map.emplace("END",      "\033[96m");
    this->color_map.emplace("PROGRESS", "\033[96m"); 
  }
  
  for ( auto& c : this->color_map )
  {
    std::string& color = c.second;
    if ( color.empty() ) continue;
    if ( color.size() > 0 && color[0]=='\033' /*&& color[1]=='3' && color[2]=='3'*/)
      continue;
    
    if ( std::isdigit(color[0]) )
    {
      color = std::string("\033[") + color + std::string("m");
      continue;
    }
    
         if ( color == "black" ) color="\033[30m";
    else if ( color == "red" ) color="\033[31m";
    else if ( color == "green" ) color="\033[32m";
    else if ( color == "brown" ) color="\033[33m";
    else if ( color == "blue" ) color="\033[34m";
    else if ( color == "magenta" ) color="\033[35m";
    else if ( color == "cyan" ) color="\033[36m";
    else if ( color == "gray" ) color="\033[37m";
    else if ( color == "dark_gray" ) color="\033[90m";
    else if ( color == "light_red" ) color="\033[91m";
    else if ( color == "light_green" ) color="\033[92m";
    else if ( color == "yellow" ) color="\033[93m";
    else if ( color == "light_blue" ) color="\033[94m";
    else if ( color == "light_magenta" ) color="\033[95m";
    else if ( color == "light_cyan" ) color="\033[96m";
    else if ( color == "white" ) color="\033[97m";
    else 
      color="\033[0m";
  }
}

}
