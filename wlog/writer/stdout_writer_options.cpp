#include "stdout_writer_options.hpp"

namespace wlog{

void stdout_writer_options::upgrade(const stdout_writer_options& other)
{
  if ( this->name.empty() ) this->name = other.name;
  if ( this->sync==-1 ) this->sync = other.sync;
}

void stdout_writer_options::finalize()
{
  if ( this->name.empty() ) this->name = "cout";
  if ( this->name=="#" ) this->name.clear();
  if ( this->sync==-1 ) this->sync = 0;
  
}

}
