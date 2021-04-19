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
  JSON_NAME(rotation_header)
  JSON_NAME(rotation_footer)
  JSON_NAME(unixtime_suffix)
  
  template<int file_writer_options:: *field>
  struct bool_getter
  {
    bool operator()(const file_writer_options& opt) const { return opt.*field!=0; }
    void operator()(file_writer_options& opt, bool value) const { opt.*field = int(value); }
  };
  
  typedef bool_getter<&file_writer_options::sync> sync;
  typedef bool_getter<&file_writer_options::startup_rotate>  startup_rotate;
  typedef bool_getter<&file_writer_options::rotation_header> rotation_header;
  typedef bool_getter<&file_writer_options::rotation_footer> rotation_footer;
  typedef bool_getter<&file_writer_options::unixtime_suffix> unixtime_suffix;

  typedef wjson::object<
    file_writer_options,
    wjson::member_list<
      wjson::member<n_path, file_writer_options, std::string, &file_writer_options::path>,
      wjson::member_p<n_sync, file_writer_options, bool, sync >,
      wjson::member_p<n_startup_rotate, file_writer_options, bool, startup_rotate>,
      wjson::member<n_size_limit, file_writer_options, long, &file_writer_options::size_limit, wjson::size_value<long,1> >,
      wjson::member<n_time_limit, file_writer_options, long, &file_writer_options::time_limit, wjson::time_interval<long,1> >,
      wjson::member<n_rotation, file_writer_options, long, &file_writer_options::rotation>,
      wjson::member_p<n_rotation_header, file_writer_options, bool, rotation_header>,
      wjson::member_p<n_rotation_footer, file_writer_options, bool, rotation_footer>,
      wjson::member_p<n_unixtime_suffix, file_writer_options, bool, unixtime_suffix>
    >,
    wjson::strict_mode
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}
