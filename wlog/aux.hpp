//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include <string>

namespace wfc{  namespace core{ namespace aux{

  std::string mkdate(bool milliseconds = false);
  
  void write_to_stream(std::ostream& os, std::string name, std::string ident,  const std::string& str, bool milliseconds );
  
  bool replace(std::string& str, const std::string& from, const std::string& to);

  void syslog_write(const std::string& sysname, const std::string& type, const std::string& str);
  
}}} // namespace
