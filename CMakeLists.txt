cmake_minimum_required(VERSION 3.22)

project(gdm)

set(CMAKE_CXX_STANDARD 17)

set(TARGET_NAME gdm)

set(INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/main
    ${CMAKE_SOURCE_DIR}/components/comp_struct
    ${CMAKE_SOURCE_DIR}/components/component
    ${CMAKE_SOURCE_DIR}/components/gdm_file
    ${CMAKE_SOURCE_DIR}/components/repo_addr_internet
    ${CMAKE_SOURCE_DIR}/components/repo_addr_project
    ${CMAKE_SOURCE_DIR}/components/repo_branch
    ${CMAKE_SOURCE_DIR}/components/repo_hints
)

add_executable(${TARGET_NAME} 
    ${CMAKE_SOURCE_DIR}/main/main.cpp
    ${CMAKE_SOURCE_DIR}/components/comp_struct/comp_struct.cpp
    ${CMAKE_SOURCE_DIR}/components/component/component.cpp
    ${CMAKE_SOURCE_DIR}/components/gdm_file/gdm_file.cpp
    ${CMAKE_SOURCE_DIR}/components/repo_addr_internet/repo_addr_internet.cpp
    ${CMAKE_SOURCE_DIR}/components/repo_addr_project/repo_addr_project.cpp
    ${CMAKE_SOURCE_DIR}/components/repo_branch/repo_branch.cpp
    ${CMAKE_SOURCE_DIR}/components/repo_hints/repo_hints.cpp
)

target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIRECTORIES})

target_compile_options(${TARGET_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)