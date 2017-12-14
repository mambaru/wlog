//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once
#include <wlog/formatter/formatter_options.hpp>
#include <wlog/writer/file_writer_options.hpp>

namespace wlog{
  
struct file_logger_options
  : formatter_options
  , file_writer_options
{
  file_logger_options& operator <<= (const file_logger_options& other);
};


}
