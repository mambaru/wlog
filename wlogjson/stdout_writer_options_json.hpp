//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wlog/writer/stdout_writer_options.hpp>
#include <wjson/json.hpp>
#include <wjson/name.hpp>

namespace wlog{

struct stdout_writer_options_json
{
  JSON_NAME(name)
  JSON_NAME(sync)

  struct sync
  {
    bool operator()(const stdout_writer_options& opt) const { return opt.sync!=0; }
    void operator()(stdout_writer_options& opt, bool value) const { opt.sync = int(value); }
  };

  typedef wjson::object<
    stdout_writer_options,
    wjson::member_list<
      wjson::member<n_name, stdout_writer_options, std::string, &stdout_writer_options::name>,
      wjson::member_p<n_sync, stdout_writer_options, bool, sync >
    >,
    wjson::strict_mode
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}
