
add_executable(test1 test1.cpp)
wci_test(TARGET test1 COMMAND test1)
target_link_libraries(test1 PUBLIC wlog)

add_executable(test2 test2.cpp)
wci_test(TARGET test2 COMMAND test2)
target_link_libraries(test2 PUBLIC wlog)

add_executable(test3 test3.cpp)
wci_test(TARGET test3 COMMAND test3)
target_link_libraries(test3 PUBLIC wlog)

add_executable(test4 test4.cpp)
wci_test(TARGET test4 COMMAND test4)
target_link_libraries(test4 PUBLIC wlog)

if (NOT WLOG_DISABLE_JSON)
  add_executable(test5 test5.cpp)
  wci_test(TARGET test5 COMMAND test5)
  target_link_libraries(test5 PUBLIC  wlog)
endif()
