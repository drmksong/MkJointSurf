include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE SOURCES "*.cpp")

add_compile_options( -gdwarf -g) # -Wall -Wextra -Wpedantic -Werror

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} raylib MkLIB jsoncpp)

