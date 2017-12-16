#include "logger_options.hpp"

namespace wlog{

static std::string expanse_path(const std::string& path, const std::string& name);
  
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

  std::string expanse_path(const std::string& path, const std::string& name)
  {
    std::string result;
    auto pos = path.rfind('.');
    if ( pos == std::string::npos )
      return path + name + std::string(".log");

    std::ptrdiff_t diff = static_cast<std::ptrdiff_t>(pos);
    return std::string( path.begin(), path.begin() + diff ) 
      + std::string("-") 
      + name 
      + std::string( path.begin() + diff, path.end() );
  }

}
