//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wlog/logger/custom_logger_options.hpp>
#include <wlogjson/basic_logger_options_json.hpp>
#include <wjson/json.hpp>
#include <wjson/name.hpp>

namespace wlog{
  
struct custom_logger_options_json
{
  JSON_NAME(names)

  typedef wjson::object<
    custom_logger_options,
    wjson::member_list<
      wjson::member<n_names, custom_logger_options, std::vector<std::string>, 
                    &custom_logger_options::names, wjson::vector_of_strings<> >,
      wjson::base<basic_logger_options_json>
    >,
    wjson::strict_mode
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};


}
