cmake_minimum_required(VERSION 3.22)

project(gdm)

set(CMAKE_CXX_STANDARD 17)

set(TARGET_NAME gdm)

set(INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/main
)

add_executable(${TARGET_NAME} 
    ${CMAKE_SOURCE_DIR}/main/main.cpp
)

target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIRECTORIES})

target_compile_options(${TARGET_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)