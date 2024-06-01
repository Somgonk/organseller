cmake_minimum_required(VERSION 3.11) 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Settings
set(PLATFORM "Web")
set(CMAKE_BUILD_TYPE "Release")

if (${PLATFORM} STREQUAL "Web")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
  set(CMAKE_EXE_LINKER_FLAGS "-s USE_GLFW=3 -s ASYNCIFY")
endif()


# Project
project(OrganSeller)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# Source Management
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Linking and such
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} raylib)

# Resource management
set(resources)
file(GLOB resource_files ${CMAKE_CURRENT_SOURCE_DIR}/resources/*)
list(APPEND resources ${resource_files})

string(APPEND resources_dir "resources")

string(APPEND resources_dir "@resources")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file ${resources_dir}")



# Web Configurations
if (${PLATFORM} STREQUAL "Web")
  # Tell Emscripten to build an example.html file.
  set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

file(COPY ${resources} DESTINATION "resources/")
