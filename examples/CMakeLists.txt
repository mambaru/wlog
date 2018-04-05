add_executable(example0 example0.cpp)
target_link_libraries(example0 wlog)

add_executable(example1 example1.cpp)
target_link_libraries(example1 wlog)

add_executable(example2 example2.cpp)
target_link_libraries(example2 wlog)

add_executable(example3 example3.cpp)
target_link_libraries(example3 wlog)

add_executable(hello hello.cpp)
target_link_libraries(hello wlog)

if (NOT WLOG_DISABLE_JSON)
  add_executable(example4 example4.cpp)
  target_link_libraries(example4 wlog)

  add_executable(example_j example_j.cpp)
  target_link_libraries(example_j wlog)
endif()
