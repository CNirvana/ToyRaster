cmake_minimum_required(VERSION 3.14.0)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME TinySR)

project(${PROJECT_NAME})

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/external/SDL2/include)

set(LIBS SDL2.lib SDL2main.lib)
link_directories(${PROJECT_SOURCE_DIR}/external/SDL2/lib/x64)

set(DLLS ${PROJECT_SOURCE_DIR}/external/SDL2/lib/x64/SDL2.dll)

file(GLOB SOURCES
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

if(WIN32)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND
    ${CMAKE_COMMAND} -E copy_if_different
    ${DLLS}
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND
    ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)
endif()