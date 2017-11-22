#pragma once
#include <string>

namespace wlog{
  
struct ilog_formatter
{
  virtual ~ilog_formatter(){}
  virtual std::string format(const std::string& name, const std::string& ident, const std::string& str) = 0;
};

// TODO
struct ifile_writer
{
  virtual ~ifile_writer(){}
  virtual void write(const std::string& str) = 0;
};

struct istdout_writer
{
  virtual ~istdout_writer(){}
  virtual void write_cout(const std::string& str) = 0;
  virtual void write_cerr(const std::string& str) = 0;
  virtual void write_clog(const std::string& str) = 0;
};

struct isyslog_writer
{
  virtual ~isyslog_writer(){}
  virtual void write(const std::string& ident, const std::string& str) = 0;
};

}
