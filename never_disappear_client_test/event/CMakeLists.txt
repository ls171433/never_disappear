file(GLOB SRC_FILES
    *.cpp
)

add_executable(test_event_dispatcher
    ${SRC_FILES}
    ${CMAKE_SOURCE_DIR}/never_disappear_client/src/event/windows/event_dispatcher.cpp
    ${CMAKE_SOURCE_DIR}/never_disappear_client/src/event/windows/simple_event.cpp
)

target_compile_definitions(test_event_dispatcher PRIVATE
    NDC_TEST
)

target_include_directories(test_event_dispatcher PRIVATE
    ${CMAKE_SOURCE_DIR}/never_disappear_client/src
)

target_link_libraries(test_event_dispatcher
    -lgtest
    -lgtest_main
)

add_test(NAME test_event_dispatcher COMMAND test_event_dispatcher)
