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
#include <sstream>

namespace wlog{

std::mutex stdout_mutex;
namespace { std::string expanse_path(const std::string& path, const std::string& name); }

  
class default_logger::impl
{
public:
  struct context
  {
    std::set<std::string> allow;
    std::set<std::string> deny;
    std::vector<after_fun> after;
    writer_fun file_writer;
    writer_fun stdout_writer;
    writer_fun syslog_writer;
  };
  
  impl( const options& copt, const handlers& hdr);
  
  bool write(
    const time_point& tp,
    const std::string& name, 
    const std::string& ident, 
    const std::string& str
  ) const;

private: 
  void init_context_(context& cntx, const logger_options& opt, const logger_handlers& hdr);

  void inherit_options_(
    const std::string& name,
    logger_options& bopt, 
    const logger_options& opt
  );
  
  bool allow_(
    const std::string& name,
    const std::string& ident, 
    const std::set<std::string>& allow,
    const std::set<std::string>& deny
  ) const;

private:
  typedef std::string key_type;
  typedef std::map<key_type, context > context_map;
  typedef std::shared_ptr<file_writer> file_writer_ptr;

  context _common;
  context_map _customize;
  std::map< std::string, file_writer_ptr > _file_map;
};


default_logger::impl::impl( const options& copt, const handlers& hdr)
{
  options opt = copt;
  init_context_( _common, opt, hdr );
  for ( auto& p : opt.customize )
  {
    inherit_options_(p.first, p.second, opt);
    
    auto itr = hdr.customize.find(p.first);
    impl::context& cntx = _customize[p.first];
    const logger_handlers& lhdr = itr!=hdr.customize.end() ? itr->second : static_cast<const logger_handlers&>(hdr);
    init_context_( cntx, p.second, lhdr );
  }

  for ( auto& p : hdr.customize )
  {
    if ( 0 == _customize.count(p.first) )
    {
      init_context_( _customize[p.first], opt, p.second );
    }
  }
}


void default_logger::impl::inherit_options_(const std::string& name, logger_options& bopt, const logger_options& opt)
{
  if ( bopt.sync == -1 )
    bopt.sync = opt.sync;

  if ( bopt.size_limit == -1 )
    bopt.size_limit = opt.size_limit;
  
  if ( bopt.rotation == -1 )
    bopt.rotation = opt.rotation;
  
  if ( bopt.colorized == colorized_flags::inherited )
    bopt.colorized = opt.colorized;
  
  if ( bopt.resolution == resolutions::inherited )
    bopt.resolution = opt.resolution;
    
  if ( bopt.path.empty() )
    bopt.path = opt.path;
  else if ( bopt.path=="#" )
    bopt.path.clear();
  else if ( bopt.path=="$" )
    bopt.path = expanse_path( opt.path, name);

  // stdout
  if ( bopt.stdout.name.empty() )
    bopt.stdout.name = opt.stdout.name;
  else if ( bopt.stdout.name=="#" )
    bopt.stdout.name.clear();
  
  if ( bopt.stdout.sync == -1 )
    bopt.stdout.sync = opt.stdout.sync!=-1 ? opt.stdout.sync : opt.sync;

  if ( bopt.stdout.resolution == resolutions::inherited )
  {
    bopt.stdout.resolution = opt.stdout.resolution!=resolutions::inherited 
                            ? opt.stdout.resolution : opt.resolution;
  }

  
  if ( bopt.stdout.colorized == colorized_flags::inherited )
  {
    bopt.stdout.colorized = opt.stdout.colorized!=colorized_flags::inherited 
                            ? opt.stdout.colorized : opt.colorized;
  }

  if ( bopt.stdout.hide == hide_flags::inherited )
  {
    bopt.stdout.hide = opt.stdout.hide!=hide_flags::inherited 
                            ? opt.stdout.hide : opt.hide;
  }

  
  

  // syslog
  if ( bopt.syslog.name.empty() )
    bopt.syslog.name = opt.syslog.name;
  else if ( bopt.syslog.name=="#" )
    bopt.syslog.name.clear();
}

void default_logger::impl::init_context_(context& cntx, /*const std::string& name,*/ const logger_options& opt, const logger_handlers& hdr)
{
  if ( hdr.file_writer!=nullptr )   cntx.file_writer = hdr.file_writer;
  if ( hdr.stdout_writer!=nullptr ) cntx.stdout_writer = hdr.stdout_writer;
  if ( hdr.syslog_writer!=nullptr ) cntx.syslog_writer = hdr.syslog_writer;
  cntx.allow = opt.allow;
  cntx.deny = opt.deny;
  if ( cntx.file_writer==nullptr && !opt.path.empty() )
  {
    auto itr = _file_map.find(opt.path);
    if ( itr == _file_map.end() )
    {
      auto fwp = std::make_shared<file_writer>( hdr.file_formatter!=nullptr ? hdr.file_formatter : formatter(opt), opt);
      itr = _file_map.emplace( opt.path, fwp ).first;
    }
    using namespace std::placeholders;
    cntx.file_writer = std::bind( &file_writer::operator(), itr->second, _1, _2, _3, _4 );
  }

  if ( cntx.stdout_writer==nullptr && !opt.stdout.name.empty() )
  {
    cntx.stdout_writer = stdout_writer( hdr.stdout_formatter!=nullptr ? hdr.stdout_formatter : formatter(opt.stdout), opt.stdout );
  }

  if ( cntx.syslog_writer==nullptr && !opt.syslog.name.empty() )
  {
    // по умолчанию без форматирования 
    cntx.syslog_writer = syslog_writer( hdr.syslog_formatter, opt.syslog );
  }
}

bool default_logger::impl::allow_(
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

bool default_logger::impl::write(
  const time_point& tp,
  const std::string& name, 
  const std::string& ident, 
  const std::string& str) const
{
  
  const auto* handlers = &_common;
  
  if ( !allow_(name, ident, handlers->allow, handlers->deny) )
    return false;

  auto itr = _customize.find(name);
  if ( itr != _customize.end() )
  {
    handlers = &(itr->second);
    if ( !allow_(name, ident, handlers->allow, handlers->deny) )
      return false;
  }
  
  if ( handlers->file_writer != nullptr )
    handlers->file_writer( tp, name, ident, str );

  if ( handlers->stdout_writer != nullptr )
  {
    handlers->stdout_writer( tp, name, ident, str );
  }

  if ( handlers->syslog_writer != nullptr )
    handlers->syslog_writer( tp, name, ident, str );

  for (const auto& after : handlers->after )
    after(tp, name, ident, str);
  
  if ( handlers != &_common )
  {
    for (const auto& after : _common.after )
      after(tp, name, ident, str);
  }
  
  return true;
}
 
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

default_logger::~default_logger()
{
  
}

default_logger::default_logger(default_logger&& other)
  : _impl( std::move(other._impl) )
{
  
}

default_logger::default_logger( const options& copt, const handlers& hdr)
  : _impl(new impl(copt, hdr) )
{
}

bool default_logger::operator()(
  const time_point& tp,
  const std::string& name, 
  const std::string& ident, 
  const std::string& str) const
{
  return _impl->write(tp, name, ident, str);
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
