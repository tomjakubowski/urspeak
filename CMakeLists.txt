cmake_minimum_required(VERSION 3.5)
project(urspeak)

# WOMM! -tjakubowski
set(DTRACE "/bin/dtrace")
set(PROBES_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/probes.d")
set(PROBES_DIR "${CMAKE_CURRENT_BINARY_DIR}/probes.dir")
set(PROBES_HEADER "${PROBES_DIR}/probes.hh")
add_custom_command(
  OUTPUT "${PROBES_HEADER}"
  COMMAND ${DTRACE} -C -h -s ${PROBES_SOURCE} -o "${PROBES_HEADER}"
  DEPENDS ${PROBES_SOURCE}
  VERBATIM)

set(PROBES_OBJ "${PROBES_DIR}/probes.o")
add_custom_command(
  OUTPUT "${PROBES_OBJ}"
  COMMAND ${DTRACE} -C -G -s "${PROBES_SOURCE}" -o "${PROBES_OBJ}"
  DEPENDS ${PROBES_SOURCE}
  VERBATIM)

if(BUILD_WITH_CLANG)
  set(CMAKE_CXX_COMPILER "clang++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(urspeak ${PROBES_OBJ} ${PROBES_HEADER} urspeak.cc)
target_include_directories(urspeak PRIVATE ${PROBES_DIR})

if(BUILD_WITH_CLANG)
  target_link_libraries(urspeak "-lc++ -lc++abi")
endif()
