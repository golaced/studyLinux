# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/projects/MotionDetect

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/projects/MotionDetect

# Include any dependencies generated for this target.
include CMakeFiles/MotionDetect.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MotionDetect.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MotionDetect.dir/flags.make

CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o: CMakeFiles/MotionDetect.dir/flags.make
CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o: MotionDetect.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/projects/MotionDetect/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o -c /home/projects/MotionDetect/MotionDetect.cpp

CMakeFiles/MotionDetect.dir/MotionDetect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MotionDetect.dir/MotionDetect.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/projects/MotionDetect/MotionDetect.cpp > CMakeFiles/MotionDetect.dir/MotionDetect.cpp.i

CMakeFiles/MotionDetect.dir/MotionDetect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MotionDetect.dir/MotionDetect.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/projects/MotionDetect/MotionDetect.cpp -o CMakeFiles/MotionDetect.dir/MotionDetect.cpp.s

CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o.requires:
.PHONY : CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o.requires

CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o.provides: CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o.requires
	$(MAKE) -f CMakeFiles/MotionDetect.dir/build.make CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o.provides.build
.PHONY : CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o.provides

CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o.provides.build: CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o

CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o: CMakeFiles/MotionDetect.dir/flags.make
CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o: xtofAffine2D.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/projects/MotionDetect/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o -c /home/projects/MotionDetect/xtofAffine2D.cpp

CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/projects/MotionDetect/xtofAffine2D.cpp > CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.i

CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/projects/MotionDetect/xtofAffine2D.cpp -o CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.s

CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o.requires:
.PHONY : CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o.requires

CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o.provides: CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o.requires
	$(MAKE) -f CMakeFiles/MotionDetect.dir/build.make CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o.provides.build
.PHONY : CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o.provides

CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o.provides.build: CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o

CMakeFiles/MotionDetect.dir/PilotData.c.o: CMakeFiles/MotionDetect.dir/flags.make
CMakeFiles/MotionDetect.dir/PilotData.c.o: PilotData.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/projects/MotionDetect/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/MotionDetect.dir/PilotData.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/MotionDetect.dir/PilotData.c.o   -c /home/projects/MotionDetect/PilotData.c

CMakeFiles/MotionDetect.dir/PilotData.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MotionDetect.dir/PilotData.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/projects/MotionDetect/PilotData.c > CMakeFiles/MotionDetect.dir/PilotData.c.i

CMakeFiles/MotionDetect.dir/PilotData.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MotionDetect.dir/PilotData.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/projects/MotionDetect/PilotData.c -o CMakeFiles/MotionDetect.dir/PilotData.c.s

CMakeFiles/MotionDetect.dir/PilotData.c.o.requires:
.PHONY : CMakeFiles/MotionDetect.dir/PilotData.c.o.requires

CMakeFiles/MotionDetect.dir/PilotData.c.o.provides: CMakeFiles/MotionDetect.dir/PilotData.c.o.requires
	$(MAKE) -f CMakeFiles/MotionDetect.dir/build.make CMakeFiles/MotionDetect.dir/PilotData.c.o.provides.build
.PHONY : CMakeFiles/MotionDetect.dir/PilotData.c.o.provides

CMakeFiles/MotionDetect.dir/PilotData.c.o.provides.build: CMakeFiles/MotionDetect.dir/PilotData.c.o

CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o: CMakeFiles/MotionDetect.dir/flags.make
CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o: xtofCalcPyrlk.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/projects/MotionDetect/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o -c /home/projects/MotionDetect/xtofCalcPyrlk.cpp

CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/projects/MotionDetect/xtofCalcPyrlk.cpp > CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.i

CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/projects/MotionDetect/xtofCalcPyrlk.cpp -o CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.s

CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o.requires:
.PHONY : CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o.requires

CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o.provides: CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o.requires
	$(MAKE) -f CMakeFiles/MotionDetect.dir/build.make CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o.provides.build
.PHONY : CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o.provides

CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o.provides.build: CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o

CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o: CMakeFiles/MotionDetect.dir/flags.make
CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o: xtofCameraCorrect.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/projects/MotionDetect/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o -c /home/projects/MotionDetect/xtofCameraCorrect.cpp

CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/projects/MotionDetect/xtofCameraCorrect.cpp > CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.i

CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/projects/MotionDetect/xtofCameraCorrect.cpp -o CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.s

CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o.requires:
.PHONY : CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o.requires

CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o.provides: CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o.requires
	$(MAKE) -f CMakeFiles/MotionDetect.dir/build.make CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o.provides.build
.PHONY : CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o.provides

CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o.provides.build: CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o

CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o: CMakeFiles/MotionDetect.dir/flags.make
CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o: xtofCameraHeight.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/projects/MotionDetect/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o -c /home/projects/MotionDetect/xtofCameraHeight.cpp

CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/projects/MotionDetect/xtofCameraHeight.cpp > CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.i

CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/projects/MotionDetect/xtofCameraHeight.cpp -o CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.s

CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o.requires:
.PHONY : CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o.requires

CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o.provides: CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o.requires
	$(MAKE) -f CMakeFiles/MotionDetect.dir/build.make CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o.provides.build
.PHONY : CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o.provides

CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o.provides.build: CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o

CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o: CMakeFiles/MotionDetect.dir/flags.make
CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o: xtofFindCorner.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/projects/MotionDetect/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o -c /home/projects/MotionDetect/xtofFindCorner.cpp

CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/projects/MotionDetect/xtofFindCorner.cpp > CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.i

CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/projects/MotionDetect/xtofFindCorner.cpp -o CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.s

CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o.requires:
.PHONY : CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o.requires

CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o.provides: CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o.requires
	$(MAKE) -f CMakeFiles/MotionDetect.dir/build.make CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o.provides.build
.PHONY : CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o.provides

CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o.provides.build: CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o

CMakeFiles/MotionDetect.dir/readSonar.c.o: CMakeFiles/MotionDetect.dir/flags.make
CMakeFiles/MotionDetect.dir/readSonar.c.o: readSonar.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/projects/MotionDetect/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/MotionDetect.dir/readSonar.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/MotionDetect.dir/readSonar.c.o   -c /home/projects/MotionDetect/readSonar.c

CMakeFiles/MotionDetect.dir/readSonar.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MotionDetect.dir/readSonar.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/projects/MotionDetect/readSonar.c > CMakeFiles/MotionDetect.dir/readSonar.c.i

CMakeFiles/MotionDetect.dir/readSonar.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MotionDetect.dir/readSonar.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/projects/MotionDetect/readSonar.c -o CMakeFiles/MotionDetect.dir/readSonar.c.s

CMakeFiles/MotionDetect.dir/readSonar.c.o.requires:
.PHONY : CMakeFiles/MotionDetect.dir/readSonar.c.o.requires

CMakeFiles/MotionDetect.dir/readSonar.c.o.provides: CMakeFiles/MotionDetect.dir/readSonar.c.o.requires
	$(MAKE) -f CMakeFiles/MotionDetect.dir/build.make CMakeFiles/MotionDetect.dir/readSonar.c.o.provides.build
.PHONY : CMakeFiles/MotionDetect.dir/readSonar.c.o.provides

CMakeFiles/MotionDetect.dir/readSonar.c.o.provides.build: CMakeFiles/MotionDetect.dir/readSonar.c.o

# Object files for target MotionDetect
MotionDetect_OBJECTS = \
"CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o" \
"CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o" \
"CMakeFiles/MotionDetect.dir/PilotData.c.o" \
"CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o" \
"CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o" \
"CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o" \
"CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o" \
"CMakeFiles/MotionDetect.dir/readSonar.c.o"

# External object files for target MotionDetect
MotionDetect_EXTERNAL_OBJECTS =

MotionDetect: CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o
MotionDetect: CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o
MotionDetect: CMakeFiles/MotionDetect.dir/PilotData.c.o
MotionDetect: CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o
MotionDetect: CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o
MotionDetect: CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o
MotionDetect: CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o
MotionDetect: CMakeFiles/MotionDetect.dir/readSonar.c.o
MotionDetect: CMakeFiles/MotionDetect.dir/build.make
MotionDetect: /usr/local/lib/libopencv_videostab.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_video.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_ts.a
MotionDetect: /usr/local/lib/libopencv_superres.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_stitching.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_photo.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_ocl.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_objdetect.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_nonfree.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_ml.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_legacy.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_imgproc.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_highgui.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_gpu.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_flann.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_features2d.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_core.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_contrib.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_calib3d.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_nonfree.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_ocl.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_gpu.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_photo.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_objdetect.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_legacy.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_video.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_ml.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_calib3d.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_features2d.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_highgui.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_imgproc.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_flann.so.2.4.10
MotionDetect: /usr/local/lib/libopencv_core.so.2.4.10
MotionDetect: CMakeFiles/MotionDetect.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable MotionDetect"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MotionDetect.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MotionDetect.dir/build: MotionDetect
.PHONY : CMakeFiles/MotionDetect.dir/build

CMakeFiles/MotionDetect.dir/requires: CMakeFiles/MotionDetect.dir/MotionDetect.cpp.o.requires
CMakeFiles/MotionDetect.dir/requires: CMakeFiles/MotionDetect.dir/xtofAffine2D.cpp.o.requires
CMakeFiles/MotionDetect.dir/requires: CMakeFiles/MotionDetect.dir/PilotData.c.o.requires
CMakeFiles/MotionDetect.dir/requires: CMakeFiles/MotionDetect.dir/xtofCalcPyrlk.cpp.o.requires
CMakeFiles/MotionDetect.dir/requires: CMakeFiles/MotionDetect.dir/xtofCameraCorrect.cpp.o.requires
CMakeFiles/MotionDetect.dir/requires: CMakeFiles/MotionDetect.dir/xtofCameraHeight.cpp.o.requires
CMakeFiles/MotionDetect.dir/requires: CMakeFiles/MotionDetect.dir/xtofFindCorner.cpp.o.requires
CMakeFiles/MotionDetect.dir/requires: CMakeFiles/MotionDetect.dir/readSonar.c.o.requires
.PHONY : CMakeFiles/MotionDetect.dir/requires

CMakeFiles/MotionDetect.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MotionDetect.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MotionDetect.dir/clean

CMakeFiles/MotionDetect.dir/depend:
	cd /home/projects/MotionDetect && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/projects/MotionDetect /home/projects/MotionDetect /home/projects/MotionDetect /home/projects/MotionDetect /home/projects/MotionDetect/CMakeFiles/MotionDetect.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MotionDetect.dir/depend
