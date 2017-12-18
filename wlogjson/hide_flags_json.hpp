//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wlog/formatter/hide_flags.hpp>
#include <wjson/json.hpp>
#include <wjson/name.hpp>

namespace wlog{
  
struct hide_flags_json
{
  JSON_NAME(none)
  JSON_NAME(date)
  JSON_NAME(time)
  JSON_NAME(year)
  JSON_NAME(month)
  JSON_NAME(weekday)
  JSON_NAME(days)
  JSON_NAME(hours)
  JSON_NAME(minutes)
  JSON_NAME(seconds)
  JSON_NAME(fraction)
  JSON_NAME(name)
  JSON_NAME(ident)
  JSON_NAME(message)
  JSON_NAME(inherited)

  typedef wjson::flags<
    hide_flags,
    wjson::member_list<
      wjson::enum_value<n_none,    hide_flags, hide_flags::none>,
      wjson::enum_value<n_date,    hide_flags, hide_flags::date>,
      wjson::enum_value<n_time,    hide_flags, hide_flags::time>,
      wjson::enum_value<n_year,    hide_flags, hide_flags::year>,
      wjson::enum_value<n_month,   hide_flags, hide_flags::month>,
      wjson::enum_value<n_weekday, hide_flags, hide_flags::weekday>,
      wjson::enum_value<n_days,    hide_flags, hide_flags::days>,
      wjson::enum_value<n_hours,   hide_flags, hide_flags::hours>,
      wjson::enum_value<n_minutes, hide_flags, hide_flags::minutes>,
      wjson::enum_value<n_seconds, hide_flags, hide_flags::seconds>,
      wjson::enum_value<n_fraction,hide_flags, hide_flags::fraction>,
      wjson::enum_value<n_name,    hide_flags, hide_flags::name>,
      wjson::enum_value<n_ident,   hide_flags, hide_flags::ident>,
      wjson::enum_value<n_message, hide_flags, hide_flags::message>,
      wjson::enum_value<n_inherited, hide_flags, hide_flags::inherited>
    >,
    '|'
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;

};

}
