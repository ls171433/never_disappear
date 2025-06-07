add_executable(never_disappear_client_test_os_looper
    os_looper_test.cpp
    ${CMAKE_SOURCE_DIR}/never_disappear_client/src/os/windows/windows_looper.cpp
)

target_compile_definitions(never_disappear_client_test_os_looper PRIVATE
    NDC_TEST
)

target_include_directories(never_disappear_client_test_os_looper PRIVATE
    ${CMAKE_SOURCE_DIR}/never_disappear_client/src
)

target_link_libraries(never_disappear_client_test_os_looper
    -lgtest
    -lgtest_main
)
