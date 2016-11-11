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
CMAKE_SOURCE_DIR = /home/lxg-/code/opencv/cameraShow

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lxg-/code/opencv/cameraShow

# Include any dependencies generated for this target.
include CMakeFiles/myapp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/myapp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/myapp.dir/flags.make

CMakeFiles/myapp.dir/imthread.cpp.o: CMakeFiles/myapp.dir/flags.make
CMakeFiles/myapp.dir/imthread.cpp.o: imthread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lxg-/code/opencv/cameraShow/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/myapp.dir/imthread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myapp.dir/imthread.cpp.o -c /home/lxg-/code/opencv/cameraShow/imthread.cpp

CMakeFiles/myapp.dir/imthread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myapp.dir/imthread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lxg-/code/opencv/cameraShow/imthread.cpp > CMakeFiles/myapp.dir/imthread.cpp.i

CMakeFiles/myapp.dir/imthread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myapp.dir/imthread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lxg-/code/opencv/cameraShow/imthread.cpp -o CMakeFiles/myapp.dir/imthread.cpp.s

CMakeFiles/myapp.dir/imthread.cpp.o.requires:

.PHONY : CMakeFiles/myapp.dir/imthread.cpp.o.requires

CMakeFiles/myapp.dir/imthread.cpp.o.provides: CMakeFiles/myapp.dir/imthread.cpp.o.requires
	$(MAKE) -f CMakeFiles/myapp.dir/build.make CMakeFiles/myapp.dir/imthread.cpp.o.provides.build
.PHONY : CMakeFiles/myapp.dir/imthread.cpp.o.provides

CMakeFiles/myapp.dir/imthread.cpp.o.provides.build: CMakeFiles/myapp.dir/imthread.cpp.o


# Object files for target myapp
myapp_OBJECTS = \
"CMakeFiles/myapp.dir/imthread.cpp.o"

# External object files for target myapp
myapp_EXTERNAL_OBJECTS =

myapp: CMakeFiles/myapp.dir/imthread.cpp.o
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
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lxg-/code/opencv/cameraShow/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable myapp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myapp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/myapp.dir/build: myapp

.PHONY : CMakeFiles/myapp.dir/build

CMakeFiles/myapp.dir/requires: CMakeFiles/myapp.dir/imthread.cpp.o.requires

.PHONY : CMakeFiles/myapp.dir/requires

CMakeFiles/myapp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/myapp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/myapp.dir/clean

CMakeFiles/myapp.dir/depend:
	cd /home/lxg-/code/opencv/cameraShow && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lxg-/code/opencv/cameraShow /home/lxg-/code/opencv/cameraShow /home/lxg-/code/opencv/cameraShow /home/lxg-/code/opencv/cameraShow /home/lxg-/code/opencv/cameraShow/CMakeFiles/myapp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/myapp.dir/depend

