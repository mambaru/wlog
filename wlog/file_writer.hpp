//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wlog/iwriter.hpp>
#include <mutex>

namespace wlog{

class file_writer
  : public iwriter
{
public:
  file_writer(const std::string& path, size_t limit, bool save_old);
  virtual void write(const std::string& str) override;
  
private:
  typedef std::mutex mutex_type;
  std::string _path;
  size_t _limit;
  bool _save_old;
  size_t _summary;
  std::string _starttime;
  mutable mutex_type _mutex;
};

}
