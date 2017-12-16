#include "stdout_logger_options.hpp"

namespace wlog{
  
void stdout_logger_options::upgrade(const stdout_logger_options& other)
{
  static_cast<formatter_options&>(*this).upgrade( static_cast<const formatter_options&>(other) );
  static_cast<stdout_writer_options&>(*this).upgrade( static_cast<const stdout_writer_options&>(other) );
}

void stdout_logger_options::finalize()
{
  if ( this->colorized == colorized_flags::inherited )
    this->colorized = colorized_flags::all;

  static_cast<formatter_options&>(*this).finalize();
  static_cast<stdout_writer_options&>(*this).finalize();
}

}
