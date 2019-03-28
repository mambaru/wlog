set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${UNIT_TEST_BIN_OUTPUT_DIR})

add_executable(test1 test1.cpp)
add_test(NAME test1 COMMAND test1)
target_link_libraries(test1 wlog)

add_executable(test2 test2.cpp)
add_test(NAME test2 COMMAND test2)
target_link_libraries(test2 wlog)

add_executable(test3 test3.cpp)
add_test(NAME test3 COMMAND test3)
target_link_libraries(test3 wlog)

add_executable(test4 test4.cpp)
add_test(NAME test4 COMMAND test4)
target_link_libraries(test4 wlog)

if ( NOT CODE_COVERAGE )
  add_test_memcheck(test1v)
  add_test_memcheck(test2v)
  add_test_memcheck(test3v)
  add_test_memcheck(test4v)
endif()

if (NOT WLOG_DISABLE_JSON)
  add_executable(test5 test5.cpp)
  add_test(NAME test5 COMMAND test5)
  target_link_libraries(test5 wlog)
  if ( NOT CODE_COVERAGE )
    add_test_memcheck(test5v)
  endif()
endif()
