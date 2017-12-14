find_package(wjson  HINTS ${CMAKE_SOURCE_DIR}/wjson/build ${CMAKE_SOURCE_DIR}/../wjson/build)
find_package(faslib HINTS ${CMAKE_SOURCE_DIR}/faslib/build ${CMAKE_SOURCE_DIR}/../faslib/build)

if (wjson_FOUND AND faslib_FOUND)
  include_directories(${WJSON_INCLUDE_DIR})
  include_directories(${FASLIB_INCLUDE_DIR})
elseif (EXISTS ${CMAKE_SOURCE_DIR}/../wjson AND EXISTS ${CMAKE_SOURCE_DIR}/../faslib)
  include_directories(${CMAKE_SOURCE_DIR}/../wjson)
  include_directories(${CMAKE_SOURCE_DIR}/../faslib)
else()
  add_definitions(-DWLOG_DISABLE_JSON)
  set( WLOG_DISABLE_JSON ON)
endif ()

add_executable(example1 example1.cpp)
target_link_libraries(example1 wlog)

add_executable(example2 example2.cpp)
target_link_libraries(example2 wlog)

add_executable(example3 example3.cpp)
target_link_libraries(example3 wlog)

if (NOT WLOG_DISABLE_JSON)
add_executable(example_j example_j.cpp)
target_link_libraries(example_j wlog)
endif()
