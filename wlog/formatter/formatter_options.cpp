//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include <wlog/formatter/formatter_options.hpp>

namespace wlog{
 
void formatter_options::upgrade(const formatter_options& other)
{
  if ( this->name_width == -1 )
    this->name_width = other.name_width;

  if ( this->ident_width == -1 )
    this->ident_width = other.ident_width;

  if ( this->resolution == resolutions::inherited )
    this->resolution = other.resolution;
  
  if ( this->hide == hide_flags::inherited )
    this->hide = other.hide;
    
  if ( this->colorized == colorized_flags::inherited) 
    this->colorized = other.colorized;
    
  if ( this->locale == "" )
    this->locale = other.locale;
    
  if ( this->datetime_format == "" )
    this->datetime_format = other.datetime_format;
      
  for (const auto& c : other.color_map)
    if ( 0 == this->color_map.count(c.first) )
      this->color_map.insert(c);
}

void formatter_options::finalize()
{
  if ( this->name_width == -1 )
    this->name_width = 8;

  if ( this->ident_width == -1 )
    this->ident_width = 9;

  if ( this->resolution == resolutions::inherited )
    this->resolution = resolutions::seconds;
  
  if ( this->hide == hide_flags::inherited )
    this->hide = hide_flags::none;
    
  if ( this->colorized == colorized_flags::inherited) 
    this->colorized = colorized_flags::none;
    
  if ( this->locale == "#" )
    this->locale.clear();

  if ( this->datetime_format == "#" )
    this->datetime_format.clear();
  
  if ( this->colorized == colorized_flags::none )
  {
    this->color_map.clear();
  }
  else
  {
    this->color_map["WARNING"] = "\033[93m";
    this->color_map["ERROR"] = "\033[91m";
    this->color_map["ERR"] = "\033[91m";
    this->color_map["FATAL"] = "\033[31m";
    this->color_map["EMERG"] = "\033[31m";
    this->color_map["CRIT"] = "\033[31m";
    this->color_map["ALERT"] = "\033[31m";
    
    if ( bool( this->colorized & colorized_flags::ident) )
    {
      this->color_map["MESSAGE"] = "\033[97m";
      this->color_map["INFO"] = "\033[97m";
      this->color_map["TRACE"] = "\033[90m";
      this->color_map["DEBUG"] = "\033[33m";
      this->color_map["BEGIN"] = "\033[36m";
      this->color_map["END"] = "\033[36m";
      this->color_map["PROGRESS"] = "\033[96m"; 
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
      //else if ( color == "none" ) color="\033[0m";
      else 
        color="\033[0m";
    }
  }
}

}
