//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wlog/writer/file_writer_options.hpp>
#include <wjson/json.hpp>
#include <wjson/name.hpp>

namespace wlog{
  
struct file_writer_options_json
{
  JSON_NAME(path)
  JSON_NAME(sync)
  JSON_NAME(startup_rotate)
  JSON_NAME(size_limit)
  JSON_NAME(time_limit)
  JSON_NAME(rotation)
  
  struct sync
  {
    // -1 по умолчанию всегда sync
    bool operator()(const file_writer_options& opt) const { return opt.sync!=0; }
    void operator()(file_writer_options& opt, bool value) const { opt.sync = int(value); }
  };

  struct startup_rotate
  {
    // по умолчанию всегда без ротации
    bool operator()(const file_writer_options& opt) const { return opt.startup_rotate > 0; }
    void operator()(file_writer_options& opt, bool value) const { opt.startup_rotate = value; }
  };

  typedef wjson::object<
    file_writer_options,
    wjson::member_list<
      wjson::member<n_path, file_writer_options, std::string, &file_writer_options::path>,
      wjson::member<n_size_limit, file_writer_options, long, &file_writer_options::size_limit>,
      wjson::member<n_time_limit, file_writer_options, long, &file_writer_options::time_limit>,
      wjson::member<n_rotation, file_writer_options, long, &file_writer_options::rotation>,
      wjson::member_p<n_startup_rotate, file_writer_options, bool, startup_rotate>,
      wjson::member_p<n_sync, file_writer_options, bool, sync >
    >,
    wjson::strict_mode
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}
