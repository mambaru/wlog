cmake_minimum_required(VERSION 2.8)
project(wlog)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(WLOG)

add_library(
  wlog
  wlog/logstream.cpp
  wlog/global_log.cpp
  wlog/init_log.cpp
  wlog/strftime.cpp
  
  wlog/formatter/formatter.cpp
  wlog/formatter/formatter_options.cpp
  wlog/formatter/formatter_handlers.cpp
  
  wlog/writer/file_writer.cpp
  wlog/writer/file_writer_options.cpp
  wlog/writer/stdout_writer.cpp
  wlog/writer/stdout_writer_options.cpp
  wlog/writer/syslog_writer.cpp
  wlog/writer/syslog_writer_options.cpp
  
  wlog/logger/default_logger.cpp
  wlog/logger/file_logger_options.cpp
  wlog/logger/stdout_logger_options.cpp
  wlog/logger/syslog_logger_options.cpp
  wlog/logger/basic_logger_options.cpp
  wlog/logger/custom_logger_options.cpp
  wlog/logger/logger_options.cpp
  wlog/logger/basic_logger_handlers.cpp
  wlog/logger/logger_handlers.cpp
  
  wlog/aux/aux.cpp
)

include_directories(.)

if ( BUILD_TESTING )
  enable_testing()
  add_subdirectory(tests)
  add_subdirectory(examples)
endif()

