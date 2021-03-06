# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lxg-/code/opencv/optical

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lxg-/code/opencv/optical

# Include any dependencies generated for this target.
include CMakeFiles/myapp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/myapp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/myapp.dir/flags.make

CMakeFiles/myapp.dir/MotionDetect.cpp.o: CMakeFiles/myapp.dir/flags.make
CMakeFiles/myapp.dir/MotionDetect.cpp.o: MotionDetect.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lxg-/code/opencv/optical/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/myapp.dir/MotionDetect.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myapp.dir/MotionDetect.cpp.o -c /home/lxg-/code/opencv/optical/MotionDetect.cpp

CMakeFiles/myapp.dir/MotionDetect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myapp.dir/MotionDetect.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lxg-/code/opencv/optical/MotionDetect.cpp > CMakeFiles/myapp.dir/MotionDetect.cpp.i

CMakeFiles/myapp.dir/MotionDetect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myapp.dir/MotionDetect.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lxg-/code/opencv/optical/MotionDetect.cpp -o CMakeFiles/myapp.dir/MotionDetect.cpp.s

CMakeFiles/myapp.dir/MotionDetect.cpp.o.requires:

.PHONY : CMakeFiles/myapp.dir/MotionDetect.cpp.o.requires

CMakeFiles/myapp.dir/MotionDetect.cpp.o.provides: CMakeFiles/myapp.dir/MotionDetect.cpp.o.requires
	$(MAKE) -f CMakeFiles/myapp.dir/build.make CMakeFiles/myapp.dir/MotionDetect.cpp.o.provides.build
.PHONY : CMakeFiles/myapp.dir/MotionDetect.cpp.o.provides

CMakeFiles/myapp.dir/MotionDetect.cpp.o.provides.build: CMakeFiles/myapp.dir/MotionDetect.cpp.o


CMakeFiles/myapp.dir/xtofAffine2D.cpp.o: CMakeFiles/myapp.dir/flags.make
CMakeFiles/myapp.dir/xtofAffine2D.cpp.o: xtofAffine2D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lxg-/code/opencv/optical/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/myapp.dir/xtofAffine2D.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myapp.dir/xtofAffine2D.cpp.o -c /home/lxg-/code/opencv/optical/xtofAffine2D.cpp

CMakeFiles/myapp.dir/xtofAffine2D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myapp.dir/xtofAffine2D.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lxg-/code/opencv/optical/xtofAffine2D.cpp > CMakeFiles/myapp.dir/xtofAffine2D.cpp.i

CMakeFiles/myapp.dir/xtofAffine2D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myapp.dir/xtofAffine2D.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lxg-/code/opencv/optical/xtofAffine2D.cpp -o CMakeFiles/myapp.dir/xtofAffine2D.cpp.s

CMakeFiles/myapp.dir/xtofAffine2D.cpp.o.requires:

.PHONY : CMakeFiles/myapp.dir/xtofAffine2D.cpp.o.requires

CMakeFiles/myapp.dir/xtofAffine2D.cpp.o.provides: CMakeFiles/myapp.dir/xtofAffine2D.cpp.o.requires
	$(MAKE) -f CMakeFiles/myapp.dir/build.make CMakeFiles/myapp.dir/xtofAffine2D.cpp.o.provides.build
.PHONY : CMakeFiles/myapp.dir/xtofAffine2D.cpp.o.provides

CMakeFiles/myapp.dir/xtofAffine2D.cpp.o.provides.build: CMakeFiles/myapp.dir/xtofAffine2D.cpp.o


CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o: CMakeFiles/myapp.dir/flags.make
CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o: xtofCalcPyrlk.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lxg-/code/opencv/optical/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o -c /home/lxg-/code/opencv/optical/xtofCalcPyrlk.cpp

CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lxg-/code/opencv/optical/xtofCalcPyrlk.cpp > CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.i

CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lxg-/code/opencv/optical/xtofCalcPyrlk.cpp -o CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.s

CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o.requires:

.PHONY : CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o.requires

CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o.provides: CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o.requires
	$(MAKE) -f CMakeFiles/myapp.dir/build.make CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o.provides.build
.PHONY : CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o.provides

CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o.provides.build: CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o


CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o: CMakeFiles/myapp.dir/flags.make
CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o: xtofCameraCorrect.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lxg-/code/opencv/optical/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o -c /home/lxg-/code/opencv/optical/xtofCameraCorrect.cpp

CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lxg-/code/opencv/optical/xtofCameraCorrect.cpp > CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.i

CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lxg-/code/opencv/optical/xtofCameraCorrect.cpp -o CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.s

CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o.requires:

.PHONY : CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o.requires

CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o.provides: CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o.requires
	$(MAKE) -f CMakeFiles/myapp.dir/build.make CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o.provides.build
.PHONY : CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o.provides

CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o.provides.build: CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o


CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o: CMakeFiles/myapp.dir/flags.make
CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o: xtofCameraHeight.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lxg-/code/opencv/optical/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o -c /home/lxg-/code/opencv/optical/xtofCameraHeight.cpp

CMakeFiles/myapp.dir/xtofCameraHeight.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myapp.dir/xtofCameraHeight.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lxg-/code/opencv/optical/xtofCameraHeight.cpp > CMakeFiles/myapp.dir/xtofCameraHeight.cpp.i

CMakeFiles/myapp.dir/xtofCameraHeight.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myapp.dir/xtofCameraHeight.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lxg-/code/opencv/optical/xtofCameraHeight.cpp -o CMakeFiles/myapp.dir/xtofCameraHeight.cpp.s

CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o.requires:

.PHONY : CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o.requires

CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o.provides: CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o.requires
	$(MAKE) -f CMakeFiles/myapp.dir/build.make CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o.provides.build
.PHONY : CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o.provides

CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o.provides.build: CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o


CMakeFiles/myapp.dir/xtofFindCorner.cpp.o: CMakeFiles/myapp.dir/flags.make
CMakeFiles/myapp.dir/xtofFindCorner.cpp.o: xtofFindCorner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lxg-/code/opencv/optical/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/myapp.dir/xtofFindCorner.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myapp.dir/xtofFindCorner.cpp.o -c /home/lxg-/code/opencv/optical/xtofFindCorner.cpp

CMakeFiles/myapp.dir/xtofFindCorner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myapp.dir/xtofFindCorner.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lxg-/code/opencv/optical/xtofFindCorner.cpp > CMakeFiles/myapp.dir/xtofFindCorner.cpp.i

CMakeFiles/myapp.dir/xtofFindCorner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myapp.dir/xtofFindCorner.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lxg-/code/opencv/optical/xtofFindCorner.cpp -o CMakeFiles/myapp.dir/xtofFindCorner.cpp.s

CMakeFiles/myapp.dir/xtofFindCorner.cpp.o.requires:

.PHONY : CMakeFiles/myapp.dir/xtofFindCorner.cpp.o.requires

CMakeFiles/myapp.dir/xtofFindCorner.cpp.o.provides: CMakeFiles/myapp.dir/xtofFindCorner.cpp.o.requires
	$(MAKE) -f CMakeFiles/myapp.dir/build.make CMakeFiles/myapp.dir/xtofFindCorner.cpp.o.provides.build
.PHONY : CMakeFiles/myapp.dir/xtofFindCorner.cpp.o.provides

CMakeFiles/myapp.dir/xtofFindCorner.cpp.o.provides.build: CMakeFiles/myapp.dir/xtofFindCorner.cpp.o


CMakeFiles/myapp.dir/camerathread.cpp.o: CMakeFiles/myapp.dir/flags.make
CMakeFiles/myapp.dir/camerathread.cpp.o: camerathread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lxg-/code/opencv/optical/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/myapp.dir/camerathread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myapp.dir/camerathread.cpp.o -c /home/lxg-/code/opencv/optical/camerathread.cpp

CMakeFiles/myapp.dir/camerathread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myapp.dir/camerathread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lxg-/code/opencv/optical/camerathread.cpp > CMakeFiles/myapp.dir/camerathread.cpp.i

CMakeFiles/myapp.dir/camerathread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myapp.dir/camerathread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lxg-/code/opencv/optical/camerathread.cpp -o CMakeFiles/myapp.dir/camerathread.cpp.s

CMakeFiles/myapp.dir/camerathread.cpp.o.requires:

.PHONY : CMakeFiles/myapp.dir/camerathread.cpp.o.requires

CMakeFiles/myapp.dir/camerathread.cpp.o.provides: CMakeFiles/myapp.dir/camerathread.cpp.o.requires
	$(MAKE) -f CMakeFiles/myapp.dir/build.make CMakeFiles/myapp.dir/camerathread.cpp.o.provides.build
.PHONY : CMakeFiles/myapp.dir/camerathread.cpp.o.provides

CMakeFiles/myapp.dir/camerathread.cpp.o.provides.build: CMakeFiles/myapp.dir/camerathread.cpp.o


# Object files for target myapp
myapp_OBJECTS = \
"CMakeFiles/myapp.dir/MotionDetect.cpp.o" \
"CMakeFiles/myapp.dir/xtofAffine2D.cpp.o" \
"CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o" \
"CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o" \
"CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o" \
"CMakeFiles/myapp.dir/xtofFindCorner.cpp.o" \
"CMakeFiles/myapp.dir/camerathread.cpp.o"

# External object files for target myapp
myapp_EXTERNAL_OBJECTS =

myapp: CMakeFiles/myapp.dir/MotionDetect.cpp.o
myapp: CMakeFiles/myapp.dir/xtofAffine2D.cpp.o
myapp: CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o
myapp: CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o
myapp: CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o
myapp: CMakeFiles/myapp.dir/xtofFindCorner.cpp.o
myapp: CMakeFiles/myapp.dir/camerathread.cpp.o
myapp: CMakeFiles/myapp.dir/build.make
myapp: /usr/local/lib/libopencv_videostab.so.2.4.9
myapp: /usr/local/lib/libopencv_ts.a
myapp: /usr/local/lib/libopencv_superres.so.2.4.9
myapp: /usr/local/lib/libopencv_stitching.so.2.4.9
myapp: /usr/local/lib/libopencv_contrib.so.2.4.9
myapp: /usr/local/lib/libopencv_nonfree.so.2.4.9
myapp: /usr/local/lib/libopencv_ocl.so.2.4.9
myapp: /usr/local/lib/libopencv_gpu.so.2.4.9
myapp: /usr/local/lib/libopencv_photo.so.2.4.9
myapp: /usr/local/lib/libopencv_objdetect.so.2.4.9
myapp: /usr/local/lib/libopencv_legacy.so.2.4.9
myapp: /usr/local/lib/libopencv_video.so.2.4.9
myapp: /usr/local/lib/libopencv_ml.so.2.4.9
myapp: /usr/local/lib/libopencv_calib3d.so.2.4.9
myapp: /usr/local/lib/libopencv_features2d.so.2.4.9
myapp: /usr/local/lib/libopencv_highgui.so.2.4.9
myapp: /usr/local/lib/libopencv_imgproc.so.2.4.9
myapp: /usr/local/lib/libopencv_flann.so.2.4.9
myapp: /usr/local/lib/libopencv_core.so.2.4.9
myapp: CMakeFiles/myapp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lxg-/code/opencv/optical/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable myapp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myapp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/myapp.dir/build: myapp

.PHONY : CMakeFiles/myapp.dir/build

CMakeFiles/myapp.dir/requires: CMakeFiles/myapp.dir/MotionDetect.cpp.o.requires
CMakeFiles/myapp.dir/requires: CMakeFiles/myapp.dir/xtofAffine2D.cpp.o.requires
CMakeFiles/myapp.dir/requires: CMakeFiles/myapp.dir/xtofCalcPyrlk.cpp.o.requires
CMakeFiles/myapp.dir/requires: CMakeFiles/myapp.dir/xtofCameraCorrect.cpp.o.requires
CMakeFiles/myapp.dir/requires: CMakeFiles/myapp.dir/xtofCameraHeight.cpp.o.requires
CMakeFiles/myapp.dir/requires: CMakeFiles/myapp.dir/xtofFindCorner.cpp.o.requires
CMakeFiles/myapp.dir/requires: CMakeFiles/myapp.dir/camerathread.cpp.o.requires

.PHONY : CMakeFiles/myapp.dir/requires

CMakeFiles/myapp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/myapp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/myapp.dir/clean

CMakeFiles/myapp.dir/depend:
	cd /home/lxg-/code/opencv/optical && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lxg-/code/opencv/optical /home/lxg-/code/opencv/optical /home/lxg-/code/opencv/optical /home/lxg-/code/opencv/optical /home/lxg-/code/opencv/optical/CMakeFiles/myapp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/myapp.dir/depend

