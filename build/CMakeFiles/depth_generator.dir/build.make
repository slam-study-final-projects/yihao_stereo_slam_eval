# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/t/slam_study/yihao_stereo_slam_eval

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/t/slam_study/yihao_stereo_slam_eval/build

# Include any dependencies generated for this target.
include CMakeFiles/depth_generator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/depth_generator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/depth_generator.dir/flags.make

CMakeFiles/depth_generator.dir/depth_generator.cc.o: CMakeFiles/depth_generator.dir/flags.make
CMakeFiles/depth_generator.dir/depth_generator.cc.o: ../depth_generator.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/t/slam_study/yihao_stereo_slam_eval/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/depth_generator.dir/depth_generator.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/depth_generator.dir/depth_generator.cc.o -c /home/t/slam_study/yihao_stereo_slam_eval/depth_generator.cc

CMakeFiles/depth_generator.dir/depth_generator.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/depth_generator.dir/depth_generator.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/t/slam_study/yihao_stereo_slam_eval/depth_generator.cc > CMakeFiles/depth_generator.dir/depth_generator.cc.i

CMakeFiles/depth_generator.dir/depth_generator.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/depth_generator.dir/depth_generator.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/t/slam_study/yihao_stereo_slam_eval/depth_generator.cc -o CMakeFiles/depth_generator.dir/depth_generator.cc.s

CMakeFiles/depth_generator.dir/depth_generator.cc.o.requires:

.PHONY : CMakeFiles/depth_generator.dir/depth_generator.cc.o.requires

CMakeFiles/depth_generator.dir/depth_generator.cc.o.provides: CMakeFiles/depth_generator.dir/depth_generator.cc.o.requires
	$(MAKE) -f CMakeFiles/depth_generator.dir/build.make CMakeFiles/depth_generator.dir/depth_generator.cc.o.provides.build
.PHONY : CMakeFiles/depth_generator.dir/depth_generator.cc.o.provides

CMakeFiles/depth_generator.dir/depth_generator.cc.o.provides.build: CMakeFiles/depth_generator.dir/depth_generator.cc.o


# Object files for target depth_generator
depth_generator_OBJECTS = \
"CMakeFiles/depth_generator.dir/depth_generator.cc.o"

# External object files for target depth_generator
depth_generator_EXTERNAL_OBJECTS =

libdepth_generator.a: CMakeFiles/depth_generator.dir/depth_generator.cc.o
libdepth_generator.a: CMakeFiles/depth_generator.dir/build.make
libdepth_generator.a: CMakeFiles/depth_generator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/t/slam_study/yihao_stereo_slam_eval/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libdepth_generator.a"
	$(CMAKE_COMMAND) -P CMakeFiles/depth_generator.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/depth_generator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/depth_generator.dir/build: libdepth_generator.a

.PHONY : CMakeFiles/depth_generator.dir/build

CMakeFiles/depth_generator.dir/requires: CMakeFiles/depth_generator.dir/depth_generator.cc.o.requires

.PHONY : CMakeFiles/depth_generator.dir/requires

CMakeFiles/depth_generator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/depth_generator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/depth_generator.dir/clean

CMakeFiles/depth_generator.dir/depend:
	cd /home/t/slam_study/yihao_stereo_slam_eval/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/t/slam_study/yihao_stereo_slam_eval /home/t/slam_study/yihao_stereo_slam_eval /home/t/slam_study/yihao_stereo_slam_eval/build /home/t/slam_study/yihao_stereo_slam_eval/build /home/t/slam_study/yihao_stereo_slam_eval/build/CMakeFiles/depth_generator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/depth_generator.dir/depend

