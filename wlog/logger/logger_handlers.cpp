#include "logger_handlers.hpp"

namespace wlog{
  
void logger_handlers::upgrade()
{
  for (auto& op : customize)
    op.second.upgrade( static_cast< const basic_logger_handlers&>(*this) );
}

  
}
