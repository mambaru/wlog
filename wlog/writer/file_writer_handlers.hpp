//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once
#include <functional>
#include <string>
#include <wlog/writer/writer_context.hpp>

namespace wlog{

struct file_writer_handlers
{
  typedef writer_context context_type;
  typedef std::function<void (std::ostream& os, const context_type& ) > context_fun;
  typedef std::function<std::string(const context_type&) > path_fun;
  context_fun header;
  context_fun footer;
  path_fun main_logname;
  path_fun rotate_logname;
};

}
