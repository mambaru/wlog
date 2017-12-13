//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/formatter/formatter_options.hpp>
#include <wlog/formatter/formatter_handlers.hpp>
#include <wlog/types.hpp>
#include <ostream>
#include <chrono>
#include <string>


namespace wlog
{

class formatter
{
public:
  
  static bool set_color(std::ostream& os, const std::string& name, const std::string& color, const formatter_options& opt);
  static void reset_color(std::ostream& os, const std::string& name, const formatter_options& opt);
  static void reset_color(std::ostream& os);
  
  static bool date( std::ostream& os, const time_point& tp, const formatter_options& opt);
  static bool time( std::ostream& os, const time_point& tp, const formatter_options& opt);

  template<typename Ratio>
  static void fraction_t(std::ostream& os, const time_point& tp);
  static bool fraction( std::ostream& os, const time_point& tp, const formatter_options& opt);
  
  static bool name( std::ostream& os, const std::string& tp, const formatter_options& opt);
  static bool ident( std::ostream& os, const std::string& tp, const formatter_options& opt);
  static bool message( std::ostream& os, const std::string& tp, const formatter_options& opt);
  
  formatter(const formatter_options& opt, const formatter_handlers& handlers = formatter_handlers() );
  
  void operator()(
    std::ostream& os, 
    const time_point& tp, 
    const std::string& name, 
    const std::string& ident, 
    const std::string& str
  ) const;
  
private:
  formatter_options _opt;
  formatter_handlers _handlers;
  bool _showtime;
  bool _showfract;
};

}
