# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zcx/graphics/eloimx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zcx/graphics/eloimx/build

# Include any dependencies generated for this target.
include out/CMakeFiles/demoJob.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include out/CMakeFiles/demoJob.dir/compiler_depend.make

# Include the progress variables for this target.
include out/CMakeFiles/demoJob.dir/progress.make

# Include the compile flags for this target's objects.
include out/CMakeFiles/demoJob.dir/flags.make

out/CMakeFiles/demoJob.dir/demoJob.cpp.o: out/CMakeFiles/demoJob.dir/flags.make
out/CMakeFiles/demoJob.dir/demoJob.cpp.o: ../src/demoJob.cpp
out/CMakeFiles/demoJob.dir/demoJob.cpp.o: out/CMakeFiles/demoJob.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zcx/graphics/eloimx/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object out/CMakeFiles/demoJob.dir/demoJob.cpp.o"
	cd /home/zcx/graphics/eloimx/build/out && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT out/CMakeFiles/demoJob.dir/demoJob.cpp.o -MF CMakeFiles/demoJob.dir/demoJob.cpp.o.d -o CMakeFiles/demoJob.dir/demoJob.cpp.o -c /home/zcx/graphics/eloimx/src/demoJob.cpp

out/CMakeFiles/demoJob.dir/demoJob.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demoJob.dir/demoJob.cpp.i"
	cd /home/zcx/graphics/eloimx/build/out && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zcx/graphics/eloimx/src/demoJob.cpp > CMakeFiles/demoJob.dir/demoJob.cpp.i

out/CMakeFiles/demoJob.dir/demoJob.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demoJob.dir/demoJob.cpp.s"
	cd /home/zcx/graphics/eloimx/build/out && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zcx/graphics/eloimx/src/demoJob.cpp -o CMakeFiles/demoJob.dir/demoJob.cpp.s

# Object files for target demoJob
demoJob_OBJECTS = \
"CMakeFiles/demoJob.dir/demoJob.cpp.o"

# External object files for target demoJob
demoJob_EXTERNAL_OBJECTS =

out/libdemoJob.a: out/CMakeFiles/demoJob.dir/demoJob.cpp.o
out/libdemoJob.a: out/CMakeFiles/demoJob.dir/build.make
out/libdemoJob.a: out/CMakeFiles/demoJob.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zcx/graphics/eloimx/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libdemoJob.a"
	cd /home/zcx/graphics/eloimx/build/out && $(CMAKE_COMMAND) -P CMakeFiles/demoJob.dir/cmake_clean_target.cmake
	cd /home/zcx/graphics/eloimx/build/out && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demoJob.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
out/CMakeFiles/demoJob.dir/build: out/libdemoJob.a
.PHONY : out/CMakeFiles/demoJob.dir/build

out/CMakeFiles/demoJob.dir/clean:
	cd /home/zcx/graphics/eloimx/build/out && $(CMAKE_COMMAND) -P CMakeFiles/demoJob.dir/cmake_clean.cmake
.PHONY : out/CMakeFiles/demoJob.dir/clean

out/CMakeFiles/demoJob.dir/depend:
	cd /home/zcx/graphics/eloimx/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zcx/graphics/eloimx /home/zcx/graphics/eloimx/src /home/zcx/graphics/eloimx/build /home/zcx/graphics/eloimx/build/out /home/zcx/graphics/eloimx/build/out/CMakeFiles/demoJob.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : out/CMakeFiles/demoJob.dir/depend
