
cmake_minimum_required(VERSION 3.16)

project(bdtk_wrapper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(third_party/glog)
# add_subdirectory(third_party/bdtk)
add_subdirectory(third_party/velox)
# add_subdirectory(third_party/googletest)

find_library(GLOG glog REQUIRED)

add_executable(glog_demo demo/glog_demo.cpp)
target_link_libraries(glog_demo glog::glog gtest)
