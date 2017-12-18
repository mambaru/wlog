//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wlog/formatter/resolutions.hpp>
#include <wjson/json.hpp>
#include <wjson/name.hpp>

namespace wlog{
  
struct resolutions_json
{
  JSON_NAME(inherited)
  JSON_NAME(nanoseconds)
  JSON_NAME(microseconds)
  JSON_NAME(milliseconds)
  JSON_NAME(centiseconds)
  JSON_NAME(deciseconds)
  JSON_NAME(seconds)
  JSON_NAME(minutes)
  JSON_NAME(hours)
  JSON_NAME(days)
  JSON_NAME(month)
  JSON_NAME(year)

  typedef wjson::enumerator<
    resolutions,
    wjson::member_list<
      wjson::enum_value<n_inherited,    resolutions, resolutions::inherited>,
      wjson::enum_value<n_nanoseconds,  resolutions, resolutions::nanoseconds>,
      wjson::enum_value<n_microseconds, resolutions, resolutions::microseconds>,
      wjson::enum_value<n_milliseconds, resolutions, resolutions::milliseconds>,
      wjson::enum_value<n_centiseconds, resolutions, resolutions::centiseconds>,
      wjson::enum_value<n_deciseconds,  resolutions, resolutions::deciseconds>,
      wjson::enum_value<n_seconds,      resolutions, resolutions::seconds>,
      wjson::enum_value<n_minutes,      resolutions, resolutions::minutes>,
      wjson::enum_value<n_hours,        resolutions, resolutions::hours>,
      wjson::enum_value<n_days,         resolutions, resolutions::days>,
      wjson::enum_value<n_month,        resolutions, resolutions::month>,
      wjson::enum_value<n_year,         resolutions, resolutions::year>
    >
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};
  
}
