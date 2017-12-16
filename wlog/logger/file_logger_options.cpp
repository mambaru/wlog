#include "file_logger_options.hpp"

namespace wlog{

void file_logger_options::upgrade(const file_logger_options& other)
{
  static_cast<formatter_options&>(*this).upgrade( static_cast<const formatter_options&>(other) );
  static_cast<file_writer_options&>(*this).upgrade( static_cast<const file_writer_options&>(other) );
}

void file_logger_options::finalize()
{
  static_cast<formatter_options&>(*this).finalize();
  static_cast<file_writer_options&>(*this).finalize();
}


}



