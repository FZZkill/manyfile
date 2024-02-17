cmake_minimum_required(VERSION 3.15)
project(Manyfile VERSION 1.0.0)
set(SOURCE
  manyfile/manyfile.cpp
  manyfile/source/line.cpp
  )
set(CMAKE_CXX_STANDARD 20)
configure_file(manyfile/cmake/config.hpp.in manyfile/include/config.hpp)
add_executable(${PROJECT_NAME} ${SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC
  ${PROJECT_BINARY_DIR}
  )
