//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/writer/syslog_writer_options.hpp>

namespace wlog{
  
struct syslog_logger_options
  : syslog_writer_options
{
  void upgrade(const syslog_logger_options& other);
  void finalize();
};

}
