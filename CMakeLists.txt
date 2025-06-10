cmake_minimum_required(VERSION 3.16)

# ---------------------------------------------------------------------
# 1. Project + compiler settings
# ---------------------------------------------------------------------
project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS  OFF)

if (MSVC)
    target_compile_options(${PROJECT_NAME} INTERFACE /W4)
else()
    add_compile_options(-Wall)
endif()

# ---------------------------------------------------------------------
# 2. Collect sources and headers
# ---------------------------------------------------------------------
file(GLOB SRC_FILES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Public include directory equivalent to “‑Iinclude”
target_include_directories(${PROJECT_NAME}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# ---------------------------------------------------------------------
# 3. Link libraries  (‑lraylib  ‑lcjson)
# ---------------------------------------------------------------------
#
# 3a. Try to locate an installed raylib first.
#     If not found, you can fall back to FetchContent or a local copy.
#
find_package(raylib QUIET)
if(raylib_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
else()
    message(STATUS "raylib not found; linking directly to -lraylib")
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
endif()

# 3b. cjson is traditionally just a system library,
#     so we link the raw import library or shared object.
find_library(CJSON_LIB cjson)
if(CJSON_LIB)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CJSON_LIB})
else()
    message(WARNING "cjson library not found in standard paths; assuming -lcjson "
                    "is available at link time")
    target_link_libraries(${PROJECT_NAME} PRIVATE cjson)
endif()


# ---------------------------------------------------------------------
# 4. Out‑of‑source build instructions (doc only)
# ---------------------------------------------------------------------
#
#   mkdir build
#   cd build
#   cmake ..          # configure step – generates Makefiles / Ninja files
#   cmake --build .   # or simply:  make
#
# The product will be “build/main”, mirroring your Makefile’s target.
#
# ---------------------------------------------------------------------
