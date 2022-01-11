cmake_minimum_required(VERSION 3.1)
project(wlog)

include(cmake/ci.cmake)

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
  wci_submodule(NAME faslib)
  wci_submodule(NAME wjson)
  list(APPEND source_list wlog/load.cpp )
endif()

if ( NOT MSVC )
  set_source_files_properties(wlog/aux/strftime.cpp PROPERTIES COMPILE_FLAGS -fno-builtin-strftime)
endif()

add_library(wlog ${source_list} )
target_include_directories(wlog PUBLIC ${wlog_SOURCE_DIR} )
if (NOT WLOG_DISABLE_JSON)
  target_link_libraries(wlog PUBLIC faslib wjson)
endif()
wci_targets(wlog)

if ( BUILD_TESTING )
  if (WLOG_DISABLE_JSON)
    wci_submodule(NAME faslib)
  endif()
  enable_testing()
  add_subdirectory(tests)
  if ( WITH_SAMPLES )
    add_subdirectory(examples)
  endif()
endif()

set(CPACK_PACKAGE_NAME "wlog")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "9")
set(CPACK_PACKAGE_VERSION_PATCH "4")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/Readme.md")
set(CPACK_PACKAGE_CONTACT "migashko@gmail.com")

install(DIRECTORY wlog DESTINATION include FILES_MATCHING PATTERN "*.hpp" )
install(TARGETS wlog LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
include(CPack)
