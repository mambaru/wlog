include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if ( NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}" )
  message(STATUS "${PROJECT_NAME} is not top level project")
  return()
endif()

include(mambaopt)
include(mambalibs)

if ( WLOG_DISABLE_JSON )
  add_definitions(-DWLOG_DISABLE_JSON)
else()
  get_faslib()
  get_mambaru(wjson WJSON_DIR "" "")
endif()



