#include "logger_options.hpp"

namespace wlog{
  
logger_options::logger_options()
{
  formatter_options::resolution = resolutions::milliseconds;
  formatter_options::hide = hide_flags::none;
  formatter_options::colorized = colorized_flags::none;
    
  file_writer_options::startup_rotate = 0;
  file_writer_options::size_limit = 0;
  file_writer_options::time_limit = 0;
  file_writer_options::rotation = 0;
  file_writer_options::sync = 1;
    
  basic_logger_options::stdout.name = "clog";
  basic_logger_options::stdout.colorized = colorized_flags::all;
}
  
void logger_options::upgrade()
{
  static_cast<formatter_options&>(this->stdout) <<= static_cast<const formatter_options&>(*this);
  if ( this->stdout.sync == -1 ) this->stdout.sync = this->sync;
  if ( this->stdout.name=="#" )  this->stdout.name.clear();
  if ( this->syslog.name=="#" )  this->syslog.name.clear();
  for (auto& op : customize)
    op.second <<= static_cast< const basic_logger_options&>(*this);
}

}
