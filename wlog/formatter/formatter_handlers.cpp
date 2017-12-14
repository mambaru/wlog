#include <wlog/formatter/formatter_handlers.hpp>
namespace wlog{

formatter_handlers& formatter_handlers::operator <<= (const formatter_handlers& other)
{
  formatter_handlers& self = *this;
  
  if ( self.date==nullptr )     self.date = other.date;
  if ( self.time==nullptr )     self.time = other.time;
  if ( self.fraction==nullptr ) self.fraction = other.fraction;
  if ( self.name==nullptr )     self.name = other.name;
  if ( self.ident==nullptr )    self.ident = other.ident;
  if ( self.message==nullptr )  self.message = other.message;
  
  return self;
}

}
