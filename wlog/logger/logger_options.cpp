#include "logger_options.hpp"
#include <wlog/aux/aux.hpp>

namespace wlog{

void logger_options::upgrade(const logger_options& other)
{
  basic_logger_options::upgrade( static_cast<const basic_logger_options&>(other) );
  for (auto& op : this->customize)
    op.upgrade( static_cast< const basic_logger_options&>(other) );
}
  
void logger_options::finalize()
{
  this->upgrade(*this);
  basic_logger_options::finalize();
  for (auto& op : customize)
  {
    if ( !op.names.empty() )
    {
      if ( op.path == "$")
      {
        op.path = expanse_path(this->path, op.names[0]);
      }
      else if ( !op.path.empty() && op.path[0] == '$' )
      {
        auto exname = std::string(op.path.begin()+1, op.path.end() );
        op.path = expanse_path(this->path, exname);
      }
    }
    op.finalize();
  }
}

custom_logger_options* logger_options::get_customize(const std::string& name)
{
  for ( custom_logger_options& c : this->customize )
  {
    for ( const auto& n : c.names)
    {
      if ( n == name)
        return &c;
    }
  }
  return nullptr;
}

}
