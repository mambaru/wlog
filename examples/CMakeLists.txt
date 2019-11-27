add_executable(example0 EXCLUDE_FROM_ALL example0.cpp)
target_link_libraries(example0 PRIVATE wlog)

add_executable(example1 EXCLUDE_FROM_ALL example1.cpp)
target_link_libraries(example1 PRIVATE wlog)

add_executable(example2 EXCLUDE_FROM_ALL example2.cpp)
target_link_libraries(example2 PRIVATE wlog)

add_executable(example3 EXCLUDE_FROM_ALL example3.cpp)
target_link_libraries(example3 PRIVATE wlog)

add_executable(hello EXCLUDE_FROM_ALL hello.cpp)
target_link_libraries(hello PRIVATE wlog)

wci_utils(example0 example1 example2 example3 hello)

if (NOT WLOG_DISABLE_JSON)
  add_executable(example4 example4.cpp)
  target_link_libraries(example4 PRIVATE wlog)

  add_executable(example_j example_j.cpp)
  target_link_libraries(example_j PRIVATE wlog)

  wci_utils(example4 example_j)
endif()
