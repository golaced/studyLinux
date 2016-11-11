cmake_minimum_required(VERSION 2.8)

#调试模式
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb") 
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

project(myapp)
find_package(OpenCV REQUIRED)
add_executable(myapp main.cpp accessTime.cpp)
target_link_libraries(myapp ${OpenCV_LIBS})

