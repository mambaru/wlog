//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <wlog/logger/logger_options.hpp>
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


struct colorized_flags_json
{
  JSON_NAME(inherited)
  JSON_NAME(none)
  JSON_NAME(date)
  JSON_NAME(time)
  JSON_NAME(fraction)
  JSON_NAME(name)
  JSON_NAME(ident_err)
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
      wjson::enum_value<n_ident_err, colorized_flags, colorized_flags::ident_err>,
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

  
  
struct formatter_options_json
{
  JSON_NAME(colorized)
  JSON_NAME(resolution)
  JSON_NAME(hide)
  JSON_NAME(locale)
  JSON_NAME(format)
  JSON_NAME(color_map)

  struct full_color
  {
    colorized_flags operator()(const formatter_options& opt) const 
    {
      return opt.colorized == colorized_flags::all ? colorized_flags::all4json : opt.colorized; 
    }
    
    void operator()(formatter_options& opt, colorized_flags value) const 
    {
      opt.colorized = value == colorized_flags::all4json ? colorized_flags::all : value;
    }
  };

  typedef wjson::object<
    formatter_options,
    wjson::member_list<
      wjson::member<n_resolution, formatter_options, resolutions, &formatter_options::resolution, resolutions_json>,
      //wjson::member<n_colorized, formatter_options, colorized_flags, &formatter_options::colorized, colorized_flags_json>,
      wjson::member_p<n_colorized, formatter_options, colorized_flags, full_color, colorized_flags_json>,
      wjson::member<n_hide, formatter_options, hide_flags, &formatter_options::hide, hide_flags_json>,
      wjson::member<n_locale, formatter_options, std::string, &formatter_options::locale>,
      wjson::member<n_format, formatter_options, std::string, &formatter_options::format>,
      wjson::member<n_color_map, formatter_options, std::map<std::string, std::string>, &formatter_options::color_map, 
                    wjson::dict_map< wjson::value<std::string> > >
    >,
    wjson::strict_mode
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

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


struct file_logger_options_json
{
  typedef wjson::object<
    file_logger_options,
    wjson::member_list<
      wjson::base<file_writer_options_json>,
      wjson::base<formatter_options_json>
    >,
    wjson::strict_mode
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

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

struct syslog_logger_options_json
{
  typedef wjson::object<
    syslog_logger_options,
    wjson::member_list<
      wjson::base<syslog_writer_options_json>
    >,
    wjson::strict_mode
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};


  
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
  
struct logger_options_json
{
  JSON_NAME(customize)
  typedef wjson::object<
    logger_options,
    wjson::member_list<
      wjson::base<basic_logger_options_json>,
      wjson::member<n_customize, logger_options, logger_options::customize_map, &logger_options::customize, wjson::dict_map<basic_logger_options_json> >
    >,
    wjson::strict_mode
  > type;
  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}
