cmake_minimum_required(VERSION 3.16)
project(FoundationXxHash)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Defaults to the godot-cpp git submodule vendored at the repo root (../../godot-cpp
# relative to this file, i.e. <repo>/godot-cpp). Override with -DGODOT_CPP_PATH=...
# to build against a different checkout.
set(GODOT_CPP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../godot-cpp" CACHE PATH "Path to Godot-cpp bindings")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" TYPE_STRING)

if(ANDROID)
    set(PLATFORM "android")
elseif(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set(PLATFORM "ios")
elseif(WIN32)
    set(PLATFORM "windows")
elseif(APPLE)
    set(PLATFORM "macos")
else()
    set(PLATFORM "linux")
endif()

if(ANDROID)
    # Godot's own arch names: arm64-v8a -> arm64, armeabi-v7a -> arm32.
    if(ANDROID_ABI STREQUAL "arm64-v8a")
        set(ARCH "arm64")
    elseif(ANDROID_ABI STREQUAL "armeabi-v7a")
        set(ARCH "arm32")
    else()
        set(ARCH "${ANDROID_ABI}")
    endif()
elseif(PLATFORM STREQUAL "ios")
    set(ARCH "arm64")
else()
    set(ARCH "x86_64")
endif()

message(STATUS "Building: ${CMAKE_BUILD_TYPE} on ${PLATFORM} ${ARCH}")
message(STATUS "GODOT_CPP_PATH: ${GODOT_CPP_PATH}")

if(NOT EXISTS "${GODOT_CPP_PATH}/CMakeLists.txt")
    message(FATAL_ERROR "godot-cpp not found at ${GODOT_CPP_PATH}. Did you run 'git submodule update --init --recursive'?")
endif()

# Build godot-cpp as part of this build (no separate SCons pre-build step needed).
add_subdirectory(${GODOT_CPP_PATH} ${CMAKE_BINARY_DIR}/godot-cpp)

file(GLOB_RECURSE SOURCES "src/private/*.cpp" "src/thirdparty/xxHash/*.c")

# iOS does not allow dynamically-loaded GDExtensions — Godot requires them
# statically linked into the exported binary there (unlike every other
# platform this addon targets).
if(PLATFORM STREQUAL "ios")
    add_library(FoundationXxHash STATIC ${SOURCES})
else()
    add_library(FoundationXxHash SHARED ${SOURCES})
endif()

target_include_directories(FoundationXxHash PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/public
    ${CMAKE_CURRENT_SOURCE_DIR}/src/thirdparty/xxHash
)

target_link_libraries(FoundationXxHash PRIVATE godot::cpp)

set_target_properties(FoundationXxHash
    PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    OUTPUT_NAME "libFoundationXxHash.${PLATFORM}.${TYPE_STRING}.${ARCH}"
)

if(NOT WIN32 AND NOT PLATFORM STREQUAL "ios")
    target_link_options(FoundationXxHash PRIVATE "-rdynamic")
endif()
