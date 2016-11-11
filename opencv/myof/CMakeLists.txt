cmake_minimum_required(VERSION 2.8)
project(myapp)
find_package(OpenCV REQUIRED)
add_executable(myapp MotionDetect.cpp xtofAffine2D.cpp xtofAffine2D.h xtofCalcPyrlk.cpp xtofCalcPyrlk.h xtofCameraCorrect.cpp xtofCameraCorrect.h xtofCameraHeight.cpp xtofCameraHeight.h xtofFindCorner.cpp xtofFindCorner.h xtofglobal.h xtofReadSonar.c xtofmavlinktest.cpp xtofmavlinktest.h)
target_link_libraries(myapp ${OpenCV_LIBS})

