cmake_minimum_required (VERSION 3.6)
project (test)

add_executable(test Source.cpp)
target_include_directories(test PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          )
add_subdirectory (API/sleepy-discord)

target_link_libraries (test sleepy-discord)