#include "file_logger_options.hpp"

namespace wlog{
  
file_logger_options& file_logger_options::operator <<= (const file_logger_options& other)
{
  file_logger_options& self = *this;
  static_cast<formatter_options&>(self) <<= static_cast<const formatter_options&>(other);
  static_cast<file_writer_options&>(self) <<= static_cast<const file_writer_options&>(other);
  return self;
}
 
}
