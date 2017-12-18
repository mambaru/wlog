//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wlogjson/stdout_writer_options_json.hpp>
#include <wlogjson/formatter_options_json.hpp>
#include <wlog/logger/stdout_logger_options.hpp>
#include <wjson/json.hpp>
#include <wjson/name.hpp>

namespace wlog{
  
struct stdout_logger_options_json
{
  typedef wjson::object<
    stdout_logger_options,
    wjson::member_list<
      wjson::base<stdout_writer_options_json>,
      wjson::base<formatter_options_json>
    >,
    wjson::strict_mode
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

  
}
