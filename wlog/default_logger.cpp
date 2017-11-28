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
namespace wlog{
  
void default_logger::initialize( const options& opt)
{
  std::lock_guard<mutex_type> lk(_mutex);
  
  // TODO:
  _opt = opt;
  if ( opt.path.empty() )
    this->_default_file_writer = nullptr;
  else if ( !opt.multilog )
  {
    using namespace std::placeholders;
    auto fw = std::make_shared<file_writer>(opt.path, opt.limit, opt.save_old);
    this->_default_file_writer = std::bind( &file_writer::write, fw, _1);
  }
  else
    this->_default_file_writer = nullptr;
    
    
}

void default_logger::write(const std::string& name, const std::string& ident, std::string str)
{
  formatter_fun formatter;
  writer_fun file_writer;
  writer_fun stdout_writer;
  syslog_fun syslog_writer;

  {
    std::lock_guard<mutex_type> lk(_mutex);
    formatter = this->get_formatter_(name);
    if ( formatter == nullptr )
      return;
    file_writer = this->get_file_writer_(name);
    stdout_writer = this->get_stdout_writer_(name);
    syslog_writer = this->get_syslog_writer_(name);
  }
  std::string logstr = formatter(name, ident, str);
  if ( logstr.empty() ) 
    return;
  if ( file_writer!=nullptr ) 
    file_writer(logstr);
  if ( stdout_writer!=nullptr ) 
    stdout_writer(logstr);
  if ( syslog_writer!=nullptr ) 
    syslog_writer(ident, str);
}

formatter_fun default_logger::get_formatter_(const std::string& name)
{
  if ( _formatter_map.empty() )
    return _default_formatter;
  auto itr = _formatter_map.find(name);
  if ( itr != _formatter_map.end() )
    return itr->second;

  if ( _opt.custom.empty() )
    return _default_formatter;
    
  auto itr2 = _opt.custom.find(name);
  if ( itr2 == _opt.custom.end() )
    return _default_formatter;
  
  using namespace std::placeholders;
  auto opt = itr2->second;
  auto fw = std::make_shared<formatter>( opt.milliseconds, opt.deny);
  formatter_fun ffun = std::bind( &formatter::format, fw, _1, _2, _3);
  _formatter_map.emplace( name, ffun );
  return ffun;
}

writer_fun default_logger::get_file_writer_(const std::string& name)
{
  if ( _file_map.empty() && !_opt.multilog )
    return this->_default_file_writer;
  
  auto itr = _file_map.find(name);
  if ( itr != _file_map.end() )
    return itr->second;
    
  auto itr2 = _opt.custom.find(name);
  if ( itr2 == _opt.custom.end() && !_opt.multilog )
    return _default_file_writer;

  using namespace std::placeholders;
  auto opt = (itr2 == _opt.custom.end() ) 
           ? static_cast<const basic_options&>(_opt) 
           : itr2->second;
  std::string path = opt.path;
  if ( path.empty() )
    path = _opt.path;
  if ( path.empty() )
    return this->_default_file_writer;

  if ( _opt.multilog ) 
  {
    auto pos = path.rfind('.');
    if ( pos == std::string::npos )
      path += name + std::string(".log");
    else
      path = std::string( path.begin(), path.begin() + pos ) + std::string("-") + name + std::string(path.begin() + pos, path.end()  );
  }
  
  auto fw = std::make_shared<file_writer>(path, opt.limit, opt.save_old);
  writer_fun wf = std::bind( &file_writer::write, fw, _1);
  _file_map.emplace( std::make_pair(name, wf) );
  return wf;
}

writer_fun default_logger::get_stdout_writer_(const std::string& name) 
{
  if ( _stdout_map.empty() && _opt.custom.empty() )
    return _default_stdout_writer;
  
  if ( !_stdout_map.empty() )
  {
    auto itr = _stdout_map.find(name);
    if ( itr != _stdout_map.end() )
      return itr->second;
  }

  auto itr = _opt.custom.find(name);
  if ( itr == _opt.custom.end() )
  {
    _stdout_map.emplace( name, _default_stdout_writer );
    return _default_stdout_writer;
  }
  
  using namespace std::placeholders;
  auto opt = itr->second;
  if ( opt.stdout.empty() )
  {
    _stdout_map.emplace( name, nullptr );
    return nullptr;
  }
    
  auto fw = std::make_shared<stdout_writer>( opt.stdout );
  writer_fun ffun = std::bind( &stdout_writer::write, fw, _1);
  _stdout_map.emplace( name, ffun );
  return ffun;
}

syslog_fun default_logger::get_syslog_writer_(const std::string& name) 
{
  if ( _syslog_map.empty() && _opt.custom.empty() )
    return _default_syslog_writer;
  
  if ( !_syslog_map.empty() )
  {
    auto itr = _syslog_map.find(name);
    if ( itr != _syslog_map.end() )
      return itr->second;
  }

  auto itr = _opt.custom.find(name);
  if ( itr == _opt.custom.end() )
  {
    _syslog_map.emplace( name, _default_syslog_writer );
    return _default_syslog_writer;
  }
  
  using namespace std::placeholders;
  auto opt = itr->second;
  if ( opt.syslog.empty() )
  {
    _syslog_map.emplace( name, nullptr );
    return nullptr;
  }
    
  auto fw = std::make_shared<syslog_writer>( opt.syslog );
  syslog_fun ffun = std::bind( &syslog_writer::write, fw, _1, _2);
  _syslog_map.emplace( name, ffun );
  return ffun;
}

}
/*
#include "default_logger.hpp"
#include "aux.hpp"

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

namespace wlog{

static std::mutex stdout_mutex;

logger_options default_logger::options() const
{
  return _conf;
}

void default_logger::initialize(const logger_options& conf)
{
  _conf = conf;
  std::sort( _conf.deny.begin(), _conf.deny.end() );
}

void default_logger::write(const std::string& name, const std::string& ident,  std::string str)
{
  if (is_deny_(name) || is_deny_(ident))
    return;
  
  while ( aux::replace(str, "\r\n", "\\r\\n") );

  if ( !_conf.path.empty() )
  {
    std::lock_guard<mutex_type> lk( _logger->_mutex);
    this->write_to_file_(name, ident, str);
  }
  
  if ( !_conf.stdout.empty() )
  {
    std::lock_guard< std::mutex> lk(stdout_mutex);
    this->write_to_stdout_(name, ident, str);
  }
  
  if ( !_conf.syslog.empty() && name == "syslog")
  {
    this->write_to_syslog_(ident, str);
  }
}

bool default_logger::is_deny_(const std::string& some) const
{
  return std::find( _conf.deny.begin(), _conf.deny.end(), some ) != _conf.deny.end();
}

void default_logger::write_to_file_(const std::string& name, const std::string& ident,  const std::string& str)
{
  std::ofstream oflog( _conf.path, std::ios_base::app );
  if ( !oflog ) return;
  if ( _conf.limit > 0 )
  {
    std::ofstream::pos_type pos = oflog.tellp();
    size_t size = static_cast<size_t>(pos);
    if ( pos!=static_cast<std::ofstream::pos_type>(-1) && size > _conf.limit )
    {
      _logger->_summary += size;
      oflog.close();
      if ( _conf.save_old )
      {
        boost::system::error_code ec;
        boost::filesystem::rename(_conf.path,_conf.path + ".old", ec);
        if ( ec )
        {
          std::cerr << "_conf.limit=" <<  _conf.limit << " size=" << size << std::endl;
          std::cerr << _conf.path << "->" << _conf.path + ".old" << std::endl;
          std::cerr << ec.message() << std::endl;
        }
      }
      oflog.open(_conf.path);
      oflog << "---------------- truncate with " << size 
            << " summary size " << _logger->_summary 
            << " ( start time: " << _logger->_starttime << ")"
            << " ----------------" << std::endl;
    }
  }

  aux::write_to_stream(oflog, name, ident, str, _conf.milliseconds);
  oflog.close();
}

void default_logger::write_to_stdout_(const std::string& name, const std::string& ident,  const std::string& str)
{
  std::ostream *p = nullptr;
  if (_conf.stdout=="cout")
    p = &std::cout;
  else if (_conf.stdout=="clog")
    p = &std::clog;
  else if (_conf.stdout=="cerr")
    p = &std::cerr;
  
  if (p)
  {
    aux::write_to_stream(*p, name, ident, str, _conf.milliseconds);
    p->flush();
  }
}

void default_logger::write_to_syslog_(const std::string& ident, const std::string& str)
{
  aux::syslog_write(_conf.syslog, ident, str);
}


}

*/
