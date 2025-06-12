cmake_minimum_required(VERSION 4.0.0)
project(never_disappear)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(never_disappear_client)
add_subdirectory(never_disappear_client_test/event)
