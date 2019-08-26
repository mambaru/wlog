#include "logger_options.hpp"
#include <wlog/aux/aux.hpp>
#include <algorithm>
namespace wlog{

void logger_options::upgrade(const logger_options& other)
{
  basic_logger_options::upgrade( static_cast<const basic_logger_options&>(other) );
  customize_list cur = std::move(this->customize);
  for (custom_logger_options clo:cur)
  {
    if ( clo.path=="$" && clo.names.size() > 1 )
    {
      for (auto name: clo.names)
      {
        this->customize.push_back(clo);
        this->customize.back().names = {name};
      }
    }
    else
    {
      this->customize.push_back(std::move(clo));
    }
  }

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
  customize_list::iterator itr = std::find_if(
    std::begin(this->customize),
    std::end(this->customize),
    [&name](custom_logger_options& c) -> bool {
      return std::find( std::begin(c.names), std::end(c.names), name) != std::end(c.names);
    }
  );

  if ( itr != std::end(this->customize) )
    return &(*itr);

  return nullptr;
}

}
