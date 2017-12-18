//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wlog/formatter/colorized_flags.hpp>
#include <wjson/json.hpp>
#include <wjson/name.hpp>

namespace wlog{

struct colorized_flags_json
{
  JSON_NAME(inherited)
  JSON_NAME(none)
  JSON_NAME(date)
  JSON_NAME(time)
  JSON_NAME(fraction)
  JSON_NAME(name)
  JSON_NAME(notice)
  JSON_NAME(ident)
  JSON_NAME(message)
  JSON_NAME(all)
  
  typedef wjson::flags<
    colorized_flags,
    wjson::member_list<
      wjson::enum_value<n_inherited, colorized_flags, colorized_flags::inherited>,
      wjson::enum_value<n_none, colorized_flags, colorized_flags::none>,
      wjson::enum_value<n_date, colorized_flags, colorized_flags::date>,
      wjson::enum_value<n_time, colorized_flags, colorized_flags::time>,
      wjson::enum_value<n_fraction, colorized_flags, colorized_flags::fraction>,
      wjson::enum_value<n_name, colorized_flags, colorized_flags::name>,
      wjson::enum_value<n_notice, colorized_flags, colorized_flags::notice>,
      wjson::enum_value<n_ident, colorized_flags, colorized_flags::ident>,
      wjson::enum_value<n_message, colorized_flags, colorized_flags::message>,
      wjson::enum_value<n_all, colorized_flags, colorized_flags::all4json >
    >,
    '|'
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}
