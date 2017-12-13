//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/formatter/formatter_options.hpp>
#include <wlog/writer/stdout_writer_options.hpp>

namespace wlog{
  
struct stdout_logger_options: formatter_options, stdout_writer_options{};

inline stdout_logger_options& operator <<= (stdout_logger_options& self, const stdout_logger_options& other)
{
  static_cast<formatter_options&>(self) <<= static_cast<const formatter_options&>(other);
  static_cast<stdout_writer_options&>(self) <<= static_cast<const stdout_writer_options&>(other);
  return self;
}

}
