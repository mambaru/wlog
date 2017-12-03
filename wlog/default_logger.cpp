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
  std::string expanse_path(const std::string& path, const std::string& name/*, bool yes*/)
  {
    /*if (!yes)
      return path;*/
    
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
  
  if ( _opt.formatter != nullptr )
  {
    _opt.allow.clear();
    _opt.deny.clear();
    _default_formatter = _opt.formatter;
  }
  
  if ( _default_formatter == nullptr )
    _default_formatter = formatter(_opt.milliseconds, _opt.deny, _opt.allow);
  
  /*
  std::string path = _opt.path;
  if ( _opt.file_writer != nullptr )
  {
    _opt.path.clear();
    _opt.multilog = false;
    _default_file_writer = opt.file_writer;
  }
  
  if ( !_opt.path.empty() && !_opt.multilog )
    _default_file_writer = file_writer( _opt.path, _opt.limit, _opt.save_old);
  */
  _default_file_writer = _opt.stdout_writer;
  if ( _default_file_writer == nullptr && !_opt.path.empty() )
    _default_file_writer = file_writer( _opt.path, _opt.limit, _opt.save_old);
  
  _default_stdout_writer = _opt.stdout_writer;
  if ( _default_stdout_writer == nullptr && !_opt.stdout.empty() )
    _default_stdout_writer = stdout_writer(_opt.stdout);

  _default_syslog_writer = _opt.syslog_writer;
  if ( _default_syslog_writer==nullptr  && !opt.syslog.empty() )
    _default_syslog_writer = syslog_writer(opt.syslog);

  for ( const auto& p : opt.custom )
  {
    const std::string& name = p.first;
    const basic_options& op = p.second;
    
    // formatter
    if ( op.formatter != nullptr )
    {
      _formatter_map.emplace(name, op.formatter);
    }
    else
    {
      _formatter_map.emplace(name, formatter(op.milliseconds, op.deny, op.allow) );
    }

    // file
    if ( op.file_writer != nullptr)
    {
      _file_map.emplace( name, op.file_writer);
    }
    else if ( !op.path.empty() )
    {
      if ( op.path == "#" )
      {
        _file_map.emplace( name, nullptr);
      }
      else if ( op.path == "$" )
      {
        _file_map.emplace( name, file_writer( expanse_path( _opt.path, name), op.limit, op.save_old));
      }
      else
      {
        _file_map.emplace( name, file_writer( op.path, op.limit, op.save_old));
      }
    }
    else if ( !_opt.path.empty() )
    {
      _file_map.emplace( name, file_writer( _opt.path, op.limit, op.save_old));
    }
    else
    {
      _file_map.emplace( name, nullptr );
    }

    // stdout
    if ( op.stdout_writer != nullptr )
    {
      _stdout_map.emplace( name, op.stdout_writer);
    }
    else if ( !op.stdout.empty() )
    {
      if ( op.stdout == "#")
      {
        _stdout_map.emplace( name, nullptr);
      }
      else if ( op.stdout == "$")
      {
        _stdout_map.emplace( name, stdout_writer(_opt.stdout));
      }
      else
      {
        _stdout_map.emplace( name, stdout_writer(op.stdout));
      }
    }
    else if ( !_opt.stdout.empty() )
    {
      _stdout_map.emplace( name, stdout_writer(_opt.stdout) );
    }
    else
    {
      _stdout_map.emplace( name, nullptr );
    }

    if ( op.syslog_writer != nullptr )
    {
      _syslog_map.emplace( name, op.syslog_writer);
    }
    else if ( !op.syslog.empty() )
    {
      _syslog_map.emplace( name, syslog_writer(op.syslog));
    }
    else
    {
      _syslog_map.emplace( name, nullptr );
    }
    
    if ( !op.after.empty() )
    {
      _after_map.emplace( name, op.after);
    }
  }
}

bool default_logger::operator()(const std::string& name, const std::string& ident, std::string str) const
{
  std::lock_guard<mutex_type> lk(log_mutex);
  
  const formatter_fun& formatter = this->get_formatter_(name);
  if ( formatter == nullptr )
    return false;

  std::string logstr = formatter(name, ident, str);
  if ( logstr.empty() ) 
    return false;
  
  if ( const writer_fun& file_writer = this->get_file_writer_(name) )
    file_writer(logstr);
  
  if ( const writer_fun& stdout_writer = this->get_stdout_writer_(name) )
    stdout_writer(logstr);
  
  if ( const syslog_fun& syslog_writer = this->get_syslog_writer_(name) )
    syslog_writer(ident, str);
  
  const auto& after = this->get_after_(name);
  for (const auto& f : after )
    f( name, ident, str);
  
  return true;
}

const formatter_fun& default_logger::get_formatter_(const std::string& name) const
{
  if ( _formatter_map.empty() )
    return _default_formatter;
  auto itr = _formatter_map.find(name);
  if ( itr != _formatter_map.end() )
    return itr->second;
  return _default_formatter;
}

const writer_fun& default_logger::get_file_writer_(const std::string& name) const
{
  if ( _file_map.empty() /*&& _opt.multilog==false*/)
    return this->_default_file_writer;
  
  auto itr = _file_map.find(name);
  if ( itr != _file_map.end() )
    return itr->second;

  return this->_default_file_writer;
  
  /*
  if ( !_opt.multilog )
  {
    static writer_fun nulfun = nullptr;
    return nulfun;
  }
 
  if ( !_opt.path.empty() )
    _file_map.emplace( name, file_writer( expanse_path( _opt.path, name, _opt.multilog), _opt.limit, _opt.save_old));
  else
    _file_map.emplace( name, nullptr );
  
  return _file_map[name];*/
}

const writer_fun& default_logger::get_stdout_writer_(const std::string& name) const
{
  if ( _stdout_map.empty() )
    return _default_stdout_writer;
  
  auto itr = _stdout_map.find(name);
  if ( itr != _stdout_map.end() )
    return itr->second;
  
  return _default_stdout_writer;
}

const syslog_fun& default_logger::get_syslog_writer_(const std::string& name) const
{
  if ( _syslog_map.empty() )
    return _default_syslog_writer;
  
  auto itr = _syslog_map.find(name);
  if ( itr != _syslog_map.end() )
    return itr->second;
  
  return _default_syslog_writer;
}

const std::vector<after_fun>& default_logger::get_after_(const std::string& name) const
{
  if ( _after_map.empty() && _opt.after.empty() )
    return _opt.after;
  auto itr = _after_map.find(name);
  if (itr!=_after_map.end() )
    return itr->second;
  return _opt.after;
}

}
