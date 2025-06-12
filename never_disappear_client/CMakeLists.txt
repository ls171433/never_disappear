file(GLOB SRC_FILES
    ${CMAKE_SOURCE_DIR}/never_disappear_client/src/*.cpp
    ${CMAKE_SOURCE_DIR}/never_disappear_client/src/*/*.cpp
    ${CMAKE_SOURCE_DIR}/never_disappear_client/src/*/*/*.cpp
)

add_executable(never_disappear_client
    ${SRC_FILES}
)

target_include_directories(never_disappear_client PUBLIC
    ${CMAKE_SOURCE_DIR}/never_disappear_client/include
)

target_include_directories(never_disappear_client PRIVATE
    ${CMAKE_SOURCE_DIR}/never_disappear_client/src
)
