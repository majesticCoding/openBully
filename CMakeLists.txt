cmake_minimum_required(VERSION 3.16)

project(openBully
        LANGUAGES C CXX)

if (NOT DEFINED BULLY_DIR)
  message(WARNING "You have not defined BULLY_DIR.")
  set(BULLY_DIR ${CMAKE_CURRENT_BINARY_DIR})
endif()

file(GLOB_RECURSE PROJECT_FILES "src/*.h" "src/*.cpp")

add_library(openBully SHARED ${PROJECT_FILES})
target_include_directories(openBully PRIVATE
  src
    src/animation
    src/area
    src/audio
    src/camera
    src/classes
    src/collision
    src/control
    src/core
      src/core/managers
    src/custom
    src/entities
    src/math
    src/memory
    src/modelinfo
    src/objects
    src/peds
    src/pickups
    src/render
    src/rw
    src/scripts
    src/vehicles
    src/weapons
)

set_target_properties(openBully PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${BULLY_DIR}"
  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BULLY_DIR}"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BULLY_DIR}"

  SUFFIX ".asi"
)

if (MSVC)
  target_compile_options(openBully PRIVATE /O2)
else()
  target_compile_options(openBully PRIVATE -O2)
endif()