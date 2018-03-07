//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//


#include "load.hpp"
#include <wjson/json.hpp>
#include <wjson/strerror.hpp>
#include <wlogjson/logger_options_json.hpp>
#include <fstream>

namespace wlog{

bool load(const std::string& src, logger_options* opt, std::string* err)
{
  std::string jsonstr;
  wjson::json_error er;

  auto beg = wjson::parser::parse_space(src.begin(), src.end(), &er);
  if ( !wjson::parser::is_object(beg, src.end()) )
  {
    std::ifstream ifs(src);
    std::copy(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>(), std::back_inserter(jsonstr));
  }
  else
    jsonstr.assign( beg, src.end());
 
  logger_options_json::serializer()(*opt, jsonstr.begin(), jsonstr.end(), &er);
  
  if ( !er )
    return true;
  
  if ( err==nullptr )
    return false;
  
  *err = wjson::strerror::message_trace(er, jsonstr.begin(), jsonstr.end());
  
  return false;
}

logger_options load(const std::string& src, std::string* err)
{
  logger_options opt;
  if ( load(src, &opt, err) )
    return opt;
  return logger_options();
}

std::string dump(const logger_options& opt)
{
  std::string res;
  logger_options_json::serializer()(opt, std::back_inserter(res) );
  return res;
}


}
