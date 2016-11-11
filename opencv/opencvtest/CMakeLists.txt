cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS_DEBUG "ENV{CXXFLAGS} -o0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "ENV{CXXFLAGS} -o3 -Wall")

project(myapp)
find_package(OpenCV REQUIRED)
add_executable(myapp testcv.cpp)
target_link_libraries(myapp ${OpenCV_LIBS})

