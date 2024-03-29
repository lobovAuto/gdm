cmake_minimum_required(VERSION 3.22)

project(gdm)

set(CMAKE_CXX_STANDARD 17)

set(TARGET_NAME gdm)

#set(UNIX true)
set(BUILD_TESTS false) #выключение тестов для более быстрой с борки libgit2
include(FetchContent)

#[===[
Начало включения библиотеки libgit2
#]===]
FetchContent_Declare(
    git
    GIT_REPOSITORY git@github.com:libgit2/libgit2.git
    GIT_TAG v1.8.0 #последняя актуальная версия на 26 марта 2024 года
)

FetchContent_GetProperties(git)

if(NOT git_POPULATED)
    FetchContent_Populate(git)
    add_subdirectory(${git_SOURCE_DIR} ${git_BINARY_DIR})
endif()
#set(BUILD_TESTS true)
#[===[
Окончание включния библиотеки libgit2
#]===]

#[===[
Начало включения библиотеки fmt
#]===]
#FetchContent_Declare(
#    fmt
#    GIT_REPOSITORY git@github.com:fmtlib/fmt.git
#    GIT_TAG 10.2.1 #последняя актуальная версия на 26 марта 2024 года
#)

#FetchContent_GetProperties(fmt)

#if(NOT fmt_POPULATED)
#    FetchContent_Populate(fmt)
#    add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR})
#endif()
#[===[
Окончание включния библиотеки fmt
#]===]

#[===[
Начало включения библиотеки boost
#]===]
#FetchContent_Declare(
#    boost
#    GIT_REPOSITORY git@github.com:boostorg/boost.git
#    GIT_TAG boost-1.84.0 #последняя актуальная версия на 26 марта 2024 года
#)

#FetchContent_GetProperties(boost)

#if(NOT boost_POPULATED)
#    FetchContent_Populate(boost)
#    add_subdirectory(${boost_SOURCE_DIR} ${boost_BINARY_DIR})
#endif()
#[===[
Окончание включния библиотеки boost
#]===]


set(INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/main
    ${CMAKE_SOURCE_DIR}/components/comp_struct
    ${CMAKE_SOURCE_DIR}/components/component
    ${CMAKE_SOURCE_DIR}/components/gdm_file
    ${CMAKE_SOURCE_DIR}/components/git_rri
    ${CMAKE_SOURCE_DIR}/components/repo_addr_internet
    ${CMAKE_SOURCE_DIR}/components/repo_addr_project
    ${CMAKE_SOURCE_DIR}/components/repo_branch
    ${CMAKE_SOURCE_DIR}/components/repo_hints
    ${CMAKE_SOURCE_DIR}/interfaces/rri

    ${git_SOURCE_DIR}/include/
) 

add_executable(${TARGET_NAME} 
    ${CMAKE_SOURCE_DIR}/main/main.cpp
    ${CMAKE_SOURCE_DIR}/components/comp_struct/comp_struct.cpp
    ${CMAKE_SOURCE_DIR}/components/component/component.cpp
    ${CMAKE_SOURCE_DIR}/components/gdm_file/gdm_file.cpp
    ${CMAKE_SOURCE_DIR}/components/git_rri/git_rri.cpp
    ${CMAKE_SOURCE_DIR}/components/repo_addr_internet/repo_addr_internet.cpp
    ${CMAKE_SOURCE_DIR}/components/repo_addr_project/repo_addr_project.cpp
    ${CMAKE_SOURCE_DIR}/components/repo_branch/repo_branch.cpp
    ${CMAKE_SOURCE_DIR}/components/repo_hints/repo_hints.cpp
)

target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(${TARGET_NAME} PRIVATE libgit2package)
#fmt boost_serialization 


target_compile_options(${TARGET_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)
