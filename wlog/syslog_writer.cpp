//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "syslog_writer.hpp"
#include <syslog.h>

namespace wlog{
  
syslog_writer::syslog_writer(const std::string& sysname, int pri)
  : _sysname(sysname)
  , _pri(pri)
{
}

void syslog_writer::write( const std::string& str)
{
  ::openlog( _sysname.c_str(), 0, LOG_USER);
  ::syslog( _pri, str.c_str());
  ::closelog();
}

}
