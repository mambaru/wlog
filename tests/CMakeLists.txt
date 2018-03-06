include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(test1 test1.cpp)
add_test(test1 test1)
add_test(test1v valgrind --error-exitcode=1 ${CMAKE_CURRENT_BINARY_DIR}/test1)
target_link_libraries(test1 wlog)

add_executable(test2 test2.cpp)
add_test(test2 test2)
add_test(test2v valgrind --error-exitcode=1 ${CMAKE_CURRENT_BINARY_DIR}/test2)
target_link_libraries(test2 wlog)

add_executable(test3 test3.cpp)
add_test(test3 test3)
add_test(test3v valgrind --error-exitcode=1 ${CMAKE_CURRENT_BINARY_DIR}/test3)
target_link_libraries(test3 wlog)

add_executable(test4 test4.cpp)
add_test(test4 test4)
add_test(test4v valgrind --error-exitcode=1 ${CMAKE_CURRENT_BINARY_DIR}/test4)
target_link_libraries(test4 wlog)
