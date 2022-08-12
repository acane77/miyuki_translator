cmake_minimum_required(VERSION 3.00)
project(extension)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# source directories
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src   SRCS)

add_library(extension SHARED ${SRCS})
target_link_libraries(extension -lmiyukiext)