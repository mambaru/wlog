#include "custom_logger_options.hpp"

namespace wlog{
  
void custom_logger_options::upgrade(const basic_logger_options& other)
{
  basic_logger_options::upgrade( other );
}

void custom_logger_options::finalize()
{
  basic_logger_options::finalize();
}


}
