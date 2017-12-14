//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/formatter/formatter_options.hpp>
#include <wlog/writer/stdout_writer_options.hpp>

namespace wlog{
  
struct stdout_logger_options
  : formatter_options
  , stdout_writer_options
{
  stdout_logger_options& operator <<= (const stdout_logger_options& other);
};


}
