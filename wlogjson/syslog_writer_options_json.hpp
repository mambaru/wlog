//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wlog/writer/syslog_writer_options.hpp>
#include <wjson/json.hpp>
#include <wjson/name.hpp>

namespace wlog{
  

struct syslog_writer_options_json
{
  JSON_NAME(name)
  typedef wjson::object<
    syslog_writer_options,
    wjson::member_list<
      wjson::member<n_name, syslog_writer_options, std::string, &syslog_writer_options::name>
    >,
    wjson::strict_mode
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};


}
