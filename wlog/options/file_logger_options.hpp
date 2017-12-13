//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once
#include <wlog/formatter/formatter_options.hpp>
#include <wlog/writer/file_writer_options.hpp>

namespace wlog{
  
struct file_logger_options: formatter_options, file_writer_options{};

inline file_logger_options& operator <<= (file_logger_options& self, const file_logger_options& other)
{
  static_cast<formatter_options&>(self) <<= static_cast<const formatter_options&>(other);
  static_cast<file_writer_options&>(self) <<= static_cast<const file_writer_options&>(other);
  return self;
}

}
