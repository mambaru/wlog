include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(test1 test1.cpp)
add_test(NAME test1 COMMAND test1)
add_test(NAME test1v COMMAND valgrind --error-exitcode=1 --leak-check=full --tool=memcheck  ${UNIT_TEST_BIN_OUTPUT_DIR}/test1)
target_link_libraries(test1 wlog)

add_executable(test2 test2.cpp)
add_test(NAME test2 COMMAND test2)
add_test(NAME test2v COMMAND valgrind --error-exitcode=1 --leak-check=full --tool=memcheck  ${UNIT_TEST_BIN_OUTPUT_DIR}/test2)
target_link_libraries(test2 wlog)

add_executable(test3 test3.cpp)
add_test(NAME test3 COMMAND test3)
add_test(NAME test3v COMMAND valgrind --error-exitcode=1 --leak-check=full --tool=memcheck  ${UNIT_TEST_BIN_OUTPUT_DIR}/test3)
target_link_libraries(test3 wlog)

add_executable(test4 test4.cpp)
add_test(NAME test4 COMMAND test4)
add_test(NAME test4v COMMAND valgrind --error-exitcode=1 --leak-check=full --tool=memcheck  ${UNIT_TEST_BIN_OUTPUT_DIR}/test4)
target_link_libraries(test4 wlog)


if (NOT WLOG_DISABLE_JSON)
  add_executable(test5 test5.cpp)
  add_test(NAME test5 COMMAND test5)
  add_test(NAME test5v COMMAND valgrind --error-exitcode=1 --leak-check=full --tool=memcheck  ${UNIT_TEST_BIN_OUTPUT_DIR}/test5)
  target_link_libraries(test5 wlog)
endif()
