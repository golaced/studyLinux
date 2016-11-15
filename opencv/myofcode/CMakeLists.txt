cmake_minimum_required(VERSION 2.8)

#debug release
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb ")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
#cmake -DCMAKE_BUILD_TYPE=Debug/Release  path

project(myapp)
find_package(OpenCV REQUIRED)
add_executable(myapp MotionDetect.cpp xtofAffine2D.cpp xtofAffine2D.h xtofCalcPyrlk.cpp xtofCalcPyrlk.h xtofCameraCorrect.cpp xtofCameraCorrect.h xtofCameraHeight.cpp xtofCameraHeight.h xtofFindCorner.cpp xtofFindCorner.h xtofglobal.h xtofReadSonar.c xtofmavlinktest.cpp xtofmavlinktest.h debug.cpp)
target_link_libraries(myapp ${OpenCV_LIBS})

