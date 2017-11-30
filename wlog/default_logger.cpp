//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "default_logger.hpp"
#include "file_writer.hpp"
#include "stdout_writer.hpp"
#include "syslog_writer.hpp"
#include "formatter.hpp"
#include <memory>
#include <iostream>

namespace wlog{

typedef std::mutex mutex_type;
extern mutex_type log_mutex;

namespace 
{
  std::string expanse_path(const std::string& path, const std::string& name, bool yes)
  {
    if (!yes)
      return path;
    
    std::string result;
    auto pos = path.rfind('.');
    if ( pos == std::string::npos )
      return path + name + std::string(".log");

    std::ptrdiff_t diff = static_cast<std::ptrdiff_t>(pos);
    return std::string( path.begin(), path.begin() + diff ) + std::string("-") + name + std::string(path.begin() + diff, path.end()  );
  }
}
   
default_logger::default_logger( const options& opt)
{
  _opt = opt;
  
  _default_formatter = formatter(opt.milliseconds, opt.deny);
  this->_default_file_writer = nullptr;
  if ( !opt.path.empty() && !opt.multilog )
    this->_default_file_writer = file_writer(opt.path, opt.limit, opt.save_old);
  this->_default_stdout_writer = nullptr;
  if ( !opt.stdout.empty() )
    this->_default_stdout_writer = stdout_writer(opt.stdout);

  this->_default_syslog_writer = nullptr;
  if ( !opt.syslog.empty() )
    this->_default_syslog_writer = syslog_writer(opt.syslog);

  for ( auto o : opt.custom )
  {
    const auto& op = o.second;
    _formatter_map.emplace( o.first, formatter(o.second.milliseconds, o.second.deny) );

    if ( !o.second.path.empty() )
      _file_map.emplace( o.first, file_writer( expanse_path( op.path, o.first, opt.multilog), op.limit, op.save_old));
    else if ( !opt.path.empty() )
      _file_map.emplace( o.first, file_writer( expanse_path( opt.path, o.first, opt.multilog), o.second.limit, o.second.save_old));
    else
      _file_map.emplace( o.first, nullptr );

    if ( !o.second.stdout.empty() )
      _stdout_map.emplace( o.first, stdout_writer(o.second.stdout));
    else
      _stdout_map.emplace( o.first, nullptr );

    if ( !o.second.syslog.empty() )
      _syslog_map.emplace( o.first, syslog_writer(o.second.syslog));
    else
      _syslog_map.emplace( o.first, nullptr );
  }
}

bool default_logger::operator()(const std::string& name, const std::string& ident, std::string str)
{
  std::lock_guard<mutex_type> lk(log_mutex);
  
  formatter_fun formatter = this->get_formatter_(name);
  if ( formatter == nullptr )
    return false;

  std::string logstr = formatter(name, ident, str);
  if ( logstr.empty() ) 
    return false;

  if ( writer_fun file_writer = this->get_file_writer_(name) )
    file_writer(logstr);
  
  if ( writer_fun stdout_writer = this->get_stdout_writer_(name) )
    stdout_writer(logstr);
  
  if ( syslog_fun syslog_writer = this->get_syslog_writer_(name) )
    syslog_writer(ident, str);
  return true;
}

formatter_fun default_logger::get_formatter_(const std::string& name)
{
  if ( _formatter_map.empty() )
    return _default_formatter;
  auto itr = _formatter_map.find(name);
  if ( itr != _formatter_map.end() )
    return itr->second;
  return _default_formatter;
}

writer_fun default_logger::get_file_writer_(const std::string& name)
{
  if ( _file_map.empty() && _opt.multilog==false)
    return this->_default_file_writer;
  
  auto itr = _file_map.find(name);
  if ( itr != _file_map.end() )
    return itr->second;
  
  if ( !_opt.multilog )
    return nullptr;
 
  if ( !_opt.path.empty() )
    _file_map.emplace( name, file_writer( expanse_path( _opt.path, name, _opt.multilog), _opt.limit, _opt.save_old));
  else
    _file_map.emplace( name, nullptr );
  
  return _file_map[name];
}

writer_fun default_logger::get_stdout_writer_(const std::string& name) 
{
  if ( _stdout_map.empty() )
    return _default_stdout_writer;
  
  auto itr = _stdout_map.find(name);
  if ( itr != _stdout_map.end() )
    return itr->second;
  
  return _default_stdout_writer;
}

syslog_fun default_logger::get_syslog_writer_(const std::string& name) 
{
  if ( _syslog_map.empty() )
    return _default_syslog_writer;
  
  auto itr = _syslog_map.find(name);
  if ( itr != _syslog_map.end() )
    return itr->second;
  
  return _default_syslog_writer;
}

}
