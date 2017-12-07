//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "default_logger.hpp"
#include "file_writer.hpp"
#include "stdout_writer.hpp"
#include "syslog_writer.hpp"
#include "formatter1.hpp"
#include <memory>
#include <iostream>
#include <sstream>

namespace wlog{

std::mutex stdout_mutex;
namespace { std::string expanse_path(const std::string& path, const std::string& name); }

default_logger::default_logger( const options& opt)
{
  this->init_handlers_(_default_options, opt);

  for ( const auto& p : opt.customize )
  {
    basic_options bopt = p.second;
    this->inherit_options_(p.first, bopt, opt);
    this->init_handlers_(_options_map[p.first], bopt);
  }
  
}

bool default_logger::operator()(
  const time_point& tp,
  const std::string& name, 
  const std::string& ident, 
  const std::string& str) const
{
  const auto* handlers = &_default_options;
  
  if ( !this->allow_(name, ident, handlers->allow, handlers->deny) )
    return false;

  auto itr = _options_map.find(name);
  if ( itr != _options_map.end() )
  {
    handlers = &(itr->second);
    if ( !this->allow_(name, ident, handlers->allow, handlers->deny) )
      return false;
  }
  
  if ( handlers->file_writer != nullptr )
    handlers->file_writer( tp, name, ident, str );

  if ( handlers->stdout_writer != nullptr )
    handlers->stdout_writer( tp, name, ident, str );

  if ( handlers->syslog_writer != nullptr )
    handlers->syslog_writer( tp, name, ident, str );

  for (const auto& after : handlers->after )
    after(tp, name, ident, str);
  
  if ( handlers != &_default_options )
  {
    for (const auto& after : _default_options.after )
      after(tp, name, ident, str);
  }
  return true;
}

void default_logger::inherit_options_(const std::string& name, basic_options& bopt, const basic_options& opt)
{
  if ( bopt.limit == -1 )
    bopt.limit = opt.limit;
  if ( bopt.save_old == -1 )
    bopt.save_old = opt.save_old;
  if ( bopt.colorized == -1 )
    bopt.colorized = opt.colorized;
  if ( bopt.resolution == resolutions::inherited )
    bopt.resolution = opt.resolution;
    
  if ( bopt.path.empty() )
    bopt.path = opt.path;
  else if ( bopt.path=="#" )
    bopt.path.clear();
  else if ( bopt.path=="$" )
    bopt.path = expanse_path( opt.path, name);

  if ( bopt.stdout.empty() )
    bopt.stdout = opt.stdout;
  else if ( bopt.stdout=="#" )
    bopt.stdout.clear();

  if ( bopt.syslog.empty() )
    bopt.syslog = opt.syslog;
  else if ( bopt.syslog=="#" )
    bopt.syslog.clear();
}

void default_logger::init_handlers_(customize_handlers& handlers, const basic_options& opt)
{
  using namespace std::placeholders;

  handlers = static_cast<const customize_handlers&>(opt);
  if ( handlers.file_formatter == nullptr )
    handlers.file_formatter  = file_formatter(opt.resolution);

  if ( handlers.stdout_formatter == nullptr )
    handlers.stdout_formatter  = stdout_formatter(opt.resolution, opt.colorized, opt.hide);
  
  if ( handlers.syslog_formatter == nullptr )
    handlers.syslog_formatter  = syslog_formatter();
    
  if ( handlers.file_writer == nullptr )
  {
    if ( !opt.path.empty() )
    {
      auto itr = _file_writer.find(opt.path);
      if ( itr == _file_writer.end() )
        itr = _file_writer.emplace( opt.path, std::make_shared<file_writer>(handlers.file_formatter, opt.path, opt.sync, opt.limit, opt.save_old) ).first;
      handlers.file_writer = std::bind( &file_writer::operator(), itr->second, _1, _2, _3, _4 );
    }
  }

  if ( handlers.stdout_writer == nullptr )
  {
    if ( !opt.stdout.empty() )
      handlers.stdout_writer = stdout_writer(handlers.stdout_formatter, opt.stdout, opt.sync);
  }

  if ( handlers.syslog_writer == nullptr )
  {
    if ( !opt.syslog.empty() )
      handlers.syslog_writer = syslog_writer(handlers.syslog_formatter, opt.syslog);
  }
}

bool default_logger::allow_(
  const std::string& name, 
  const std::string& ident,
  const std::set<std::string>& allow,
  const std::set<std::string>& deny
) const
{
  return 
    ( allow.empty() || allow.count(name)!=0 || allow.count(ident)!=0 )
    &&
    ( deny.empty() || (deny.count(name)==0 && deny.count(ident)==0 ) );
}



namespace 
{
  std::string expanse_path(const std::string& path, const std::string& name)
  {
    std::string result;
    auto pos = path.rfind('.');
    if ( pos == std::string::npos )
      return path + name + std::string(".log");

    std::ptrdiff_t diff = static_cast<std::ptrdiff_t>(pos);
    return std::string( path.begin(), path.begin() + diff ) 
      + std::string("-") 
      + name 
      + std::string( path.begin() + diff, path.end() );
  }
}

}
