cmake_minimum_required(VERSION 3.0.0)
project(chacha20 VERSION 0.1.0)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(src)
add_library(c_chacha20   src/chacha20.c)
add_library(cpp_chacha20 src/chacha20.cpp)


add_executable(validity_check tests/validity_check.cpp)
add_executable(c_speed_test tests/speedtest.c)
add_executable(cpp_speed_test tests/speedtest.cpp)

set_source_files_properties(test.c speedtest.c PROPERTIES LANGUAGE C)

target_link_libraries(c_speed_test c_chacha20)
target_link_libraries(cpp_speed_test cpp_chacha20)
target_link_libraries(validity_check cpp_chacha20 c_chacha20)