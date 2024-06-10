cmake_minimum_required(VERSION 3.22)

project(gdm)

set(CMAKE_CXX_STANDARD 17)

set(TARGET_NAME gdm)


include(FetchContent)


add_subdirectory(/home/lobov/workspace/boost ${CMAKE_SOURCE_DIR}/build/__deps EXCLUDE_FROM_ALL)

set(INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/main
    ${CMAKE_SOURCE_DIR}/components/comp_struct
    ${CMAKE_SOURCE_DIR}/components/component
    ${CMAKE_SOURCE_DIR}/components/gdm_file
    ${CMAKE_SOURCE_DIR}/components/git_rri
    ${CMAKE_SOURCE_DIR}/interfaces/rri

    ${boost_SOURCE_DIR}/lib/process/include/
) 

add_executable(${TARGET_NAME} 
    ${CMAKE_SOURCE_DIR}/main/main.cpp
    ${CMAKE_SOURCE_DIR}/main/help.cpp
    ${CMAKE_SOURCE_DIR}/components/comp_struct/comp_struct.cpp
    ${CMAKE_SOURCE_DIR}/components/component/component.cpp
    ${CMAKE_SOURCE_DIR}/components/gdm_file/gdm_file.cpp
    ${CMAKE_SOURCE_DIR}/components/git_rri/git_rri.cpp
)

target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(${TARGET_NAME} PRIVATE boost_process)


target_compile_options(${TARGET_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND cp ${CMAKE_SOURCE_DIR}/help.txt ${CMAKE_SOURCE_DIR}/build/help.txt)

