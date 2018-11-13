cmake_minimum_required(VERSION 3.1)
project(wlog)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ci)

if ( STANDALONE )
  getlibs(faslib wjson)
endif()

include_directories(.)
set(
  source_list
  wlog/init.cpp

  wlog/global/logstream.cpp
  wlog/global/stdstream.cpp
  wlog/global/global_log.cpp
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
  wlog/aux/strftime.cpp
)

if (NOT WLOG_DISABLE_JSON)
  list(APPEND source_list wlog/load.cpp )
endif()

add_library(wlog ${source_list})

if ( BUILD_TESTING )
  enable_testing()
  add_subdirectory(tests)
  add_subdirectory(examples)
endif()

set(CPACK_PACKAGE_NAME "wlog")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "7")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/Readme.md")
set(CPACK_PACKAGE_CONTACT "migashko@gmail.com")

install(DIRECTORY wlog DESTINATION include FILES_MATCHING PATTERN "*.hpp" )
install(TARGETS wlog LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
include(CPack)
