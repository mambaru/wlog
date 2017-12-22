//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <mutex>
#include <memory>
#include <wlog/logger_fun.hpp>
#include <wlog/writer/file_writer_options.hpp>
#include <wlog/writer/file_writer_handlers.hpp>
#include <wlog/writer/writer_context.hpp>
#include <fstream>
#include <list>

namespace wlog{

class file_writer final
{
public:
  ~file_writer();
  typedef file_writer_options options;
  typedef file_writer_handlers handlers;
  typedef writer_context context_type;
  
  file_writer(const formatter_fun& formatter, const options& opt, const handlers& hdlr = handlers() );
  
  void operator()(  
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  );
  
private:
  void write_(  
    std::ofstream& oflog,
    const time_point& tp,
    const std::string& name, 
    const std::string& ident,
    const std::string& str
  );
  
  bool rotate_if_( std::ofstream& oflog);
  void rotate_( std::ofstream& oflog);

private:
  static handlers upd_handlers( const options& , const handlers& hdlr );
  static void write_header(std::ostream& os, const context_type& contex);
  static void write_footer(std::ostream& os,const context_type& contex);
  static std::string main_logname(const context_type& contex);
  static std::string rotate_logname(const context_type& contex);
private:
  context_type _contex;
  handlers _handlers;
  std::ofstream _flog;
};

}
