project(FixClientLibrary)

# --------- --------- -------- ---------
# Library

# Add all sources in the SRC tree
file( GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
file( GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp )

add_library(${PROJECT_NAME} ${SOURCES})

# add_dependencies(${PROJECT_NAME}
# )

target_link_libraries(${PROJECT_NAME}
  PUBLIC
      fmt::fmt
      ${QuickFixLibrary}
)

# Search for includes in the named include folder
target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/include/fixclient
    ${CMAKE_INSTALL_PREFIX}/include
    /usr/local/include
    ${HOMEBREW_INCLUDE_DIR}
)

# --------- --------- -------- ---------
# Installer

install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

INSTALL(DIRECTORY include/fixclient DESTINATION "include")
