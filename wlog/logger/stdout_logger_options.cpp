#include "stdout_logger_options.hpp"

namespace wlog{
  
stdout_logger_options& stdout_logger_options::operator <<= (const stdout_logger_options& other)
{
  stdout_logger_options& self = *this;
  static_cast<formatter_options&>(self) <<= static_cast<const formatter_options&>(other);
  static_cast<stdout_writer_options&>(self) <<= static_cast<const stdout_writer_options&>(other);
  return self;
}

}
