//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wlog/formatter/formatter_options.hpp>
#include <wlogjson/resolutions_json.hpp>
#include <wlogjson/colorized_flags_json.hpp>
#include <wlogjson/hide_flags_json.hpp>
#include <wjson/json.hpp>
#include <wjson/name.hpp>

namespace wlog{
  
struct formatter_options_json
{
  JSON_NAME(colorized)
  JSON_NAME(resolution)
  JSON_NAME(hide)
  JSON_NAME(locale)
  JSON_NAME(datetime_format)
  JSON_NAME(color_map)

  struct full_color
  {
    colorized_flags operator()(const formatter_options& opt) const 
    {
      return opt.colorized == colorized_flags::all ? colorized_flags::all4json : opt.colorized; 
    }
    
    void operator()(formatter_options& opt, colorized_flags value) const 
    {
      opt.colorized = value == colorized_flags::all4json ? colorized_flags::all : value;
    }
  };

  typedef wjson::object<
    formatter_options,
    wjson::member_list<
      wjson::member<n_resolution, formatter_options, resolutions, &formatter_options::resolution, resolutions_json>,
      wjson::member_p<n_colorized, formatter_options, colorized_flags, full_color, colorized_flags_json>,
      wjson::member<n_hide, formatter_options, hide_flags, &formatter_options::hide, hide_flags_json>,
      wjson::member<n_locale, formatter_options, std::string, &formatter_options::locale>,
      wjson::member<n_datetime_format, formatter_options, std::string, &formatter_options::datetime_format>,
      wjson::member<n_color_map, formatter_options, std::map<std::string, std::string>, &formatter_options::color_map, 
                    wjson::dict_map< wjson::value<std::string> > >
    >,
    wjson::strict_mode
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};


}
