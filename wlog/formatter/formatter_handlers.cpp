#include <wlog/formatter/formatter_handlers.hpp>
namespace wlog{

void formatter_handlers::upgrade(const formatter_handlers& other)
{
  if ( this->date==nullptr )
    this->date = other.date;
  if ( this->time==nullptr )
    this->time = other.time;
  if ( this->fraction==nullptr )
    this->fraction = other.fraction;
  if ( this->name==nullptr )
    this->name = other.name;
  if ( this->ident==nullptr )
    this->ident = other.ident;
  if ( this->message==nullptr )
    this->message = other.message;
}

}
