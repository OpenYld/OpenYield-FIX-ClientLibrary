# This is the APT version for Ubuntu 22.04
cmake_minimum_required(VERSION 3.22.1)

project(OpenYield-FIX-ClientLibrary)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_VISIBILITY_PRESET default)
# set(CMAKE_VISIBILITY_INLINES_HIDDEN 0)

# set(CMAKE_VERBOSE_MAKEFILE ON)

# Set to ON to build with Shared Libraries!
if(APPLE)
  option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
else()
  option(BUILD_SHARED_LIBS OFF)
endif()

# Lots of warnings and all warnings as errors
# Do not add -Weverything because it generates old C++98 errors
# Defines DEBUG for Debug Builds, TEST for Test Builds
add_compile_options(
  "-Wall" "-Wextra" "-Wpedantic" "-Werror" "-fPIC"
  "$<$<CONFIG:DEBUG>:-DDEBUG>"
  "$<$<CONFIG:TEST>:-DTEST>"
)

message("-- Building for ${CMAKE_BUILD_TYPE}")

# Set install folder
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX
    $ENV{HOME}/Applications CACHE
    PATH "Default installation path"
    FORCE
  )
endif()

message("-- Install prefix set to ${CMAKE_INSTALL_PREFIX}")

# # Add our library folder to the MACOS RPath
# # E.g. `otool -L LogService` shows `@rpath` for Libraries
set(CMAKE_MACOSX_RPATH ON)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# Platform Specific

if(APPLE)
  # Get system architecture
  if (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
      set (X86 TRUE)
  else ()
      set (X86 FALSE)
  endif ()

  if(X86)
    set(HOMEBREW_ROOT "/usr/local")
    message("-- Homebrew set to INTEL (${HOMEBREW_ROOT})")
  else()
    set(HOMEBREW_ROOT "/opt/homebrew")
    message("-- Homebrew set to ARM64 (${HOMEBREW_ROOT})")
  endif()

  set(OPENSSL_ROOT_DIR "${HOMEBREW_ROOT}/Cellar/openssl@1.1/1.1.1u")
  set(HOMEBREW_INCLUDE_DIR "${HOMEBREW_ROOT}/include")
  set(HOMEBREW_LIB_DIR "${HOMEBREW_ROOT}/lib")
endif()

# Dependencies for all
find_library(QuickFixLibrary NAMES QUICKFIX libquickfix.so REQUIRED)
find_package(fmt REQUIRED)

# Add Product Components
add_subdirectory(FixClientLibrary)
