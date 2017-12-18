//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wlog/logger/basic_logger_options.hpp>
#include <wlogjson/file_logger_options_json.hpp>
#include <wlogjson/stdout_logger_options_json.hpp>
#include <wlogjson/syslog_logger_options_json.hpp>
#include <wjson/json.hpp>
#include <wjson/name.hpp>
#include <set>

namespace wlog{
  
struct basic_logger_options_json
{
  typedef wjson::array< std::set< wjson::value<std::string> > > string_set_json;
  JSON_NAME(allow)
  JSON_NAME(deny)
  JSON_NAME(stdout)
  JSON_NAME(syslog)

  typedef wjson::object<
    basic_logger_options,
    wjson::member_list<
      wjson::base<file_logger_options_json>,
      wjson::member<n_allow,  basic_logger_options, std::set<std::string>, &basic_logger_options::allow, string_set_json>,
      wjson::member<n_deny,   basic_logger_options, std::set<std::string>, &basic_logger_options::deny, string_set_json>,
      wjson::member<n_stdout, basic_logger_options, stdout_logger_options, &basic_logger_options::stdout, stdout_logger_options_json>,
      wjson::member<n_syslog, basic_logger_options, syslog_logger_options, &basic_logger_options::syslog, syslog_logger_options_json>
    >,
    wjson::strict_mode
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}
