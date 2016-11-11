cmake_minimum_required(VERSION 2.8)
project(myapp)
find_package(OpenCV REQUIRED)
add_executable(myapp imthread.cpp camerathread.cpp camerathread.h)
target_link_libraries(myapp ${OpenCV_LIBS})

