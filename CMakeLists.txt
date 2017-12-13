cmake_minimum_required(VERSION 3.0)

project(wlog)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror -pedantic -fno-rtti -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-O2 -g -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")


if (PARANOID_WARNING)
  message(STATUS "PARANOID_WARNING ON")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align \
 -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization\
 -Wformat=2 -Winit-self -Wmissing-declarations \
 -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual \
 -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
 -Wstrict-overflow=5 -Wswitch-default -Wundef ")
endif()

include_directories(.)

if ( BUILD_TESTING )
  enable_testing()
  add_subdirectory(tests)
  add_subdirectory(examples)
endif()

add_library(
 wlog
 wlog/logstream.cpp
 wlog/global_log.cpp
 wlog/default_logger.cpp
 wlog/formatter.cpp
 wlog/file_writer.cpp
 wlog/stdout_writer.cpp
 wlog/syslog_writer.cpp
)

include(CMakePackageConfigHelpers)
set(LIB_INSTALL_DIR lib/ )
set(LIB_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR} )
set(INCLUDE_INSTALL_DIR wlog)
set(INCLUDE_CURRENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
configure_package_config_file(
  cmake/Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/wlogConfig.cmake
  INSTALL_DESTINATION ${LIB_INSTALL_DIR}/wlog/cmake
  PATH_VARS INCLUDE_INSTALL_DIR INCLUDE_CURRENT_DIR LIB_BUILD_DIR LIB_INSTALL_DIR
)
#SYSCONFIG_INSTALL_DIR 

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/wlogConfigVersion.cmake
  VERSION 1.2.3
  COMPATIBILITY SameMajorVersion
)

install(
  FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/wlogConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/wlogConfigVersion.cmake
  DESTINATION 
    ${LIB_INSTALL_DIR}/wlog/cmake 
)
        
