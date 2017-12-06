cmake_minimum_required(VERSION 2.6)

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
                         
      # -Wlogical-op -Wnoexcept -Wstrict-null-sentinel  -Werror
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
