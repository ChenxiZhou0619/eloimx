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
include out/CMakeFiles/eloimx.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include out/CMakeFiles/eloimx.dir/compiler_depend.make

# Include the progress variables for this target.
include out/CMakeFiles/eloimx.dir/progress.make

# Include the compile flags for this target's objects.
include out/CMakeFiles/eloimx.dir/flags.make

out/CMakeFiles/eloimx.dir/main.cpp.o: out/CMakeFiles/eloimx.dir/flags.make
out/CMakeFiles/eloimx.dir/main.cpp.o: ../src/main.cpp
out/CMakeFiles/eloimx.dir/main.cpp.o: out/CMakeFiles/eloimx.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zcx/graphics/eloimx/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object out/CMakeFiles/eloimx.dir/main.cpp.o"
	cd /home/zcx/graphics/eloimx/build/out && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT out/CMakeFiles/eloimx.dir/main.cpp.o -MF CMakeFiles/eloimx.dir/main.cpp.o.d -o CMakeFiles/eloimx.dir/main.cpp.o -c /home/zcx/graphics/eloimx/src/main.cpp

out/CMakeFiles/eloimx.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eloimx.dir/main.cpp.i"
	cd /home/zcx/graphics/eloimx/build/out && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zcx/graphics/eloimx/src/main.cpp > CMakeFiles/eloimx.dir/main.cpp.i

out/CMakeFiles/eloimx.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eloimx.dir/main.cpp.s"
	cd /home/zcx/graphics/eloimx/build/out && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zcx/graphics/eloimx/src/main.cpp -o CMakeFiles/eloimx.dir/main.cpp.s

# Object files for target eloimx
eloimx_OBJECTS = \
"CMakeFiles/eloimx.dir/main.cpp.o"

# External object files for target eloimx
eloimx_EXTERNAL_OBJECTS =

out/eloimx: out/CMakeFiles/eloimx.dir/main.cpp.o
out/eloimx: out/CMakeFiles/eloimx.dir/build.make
out/eloimx: out/libdemoJob.a
out/eloimx: out/bsdfs/libbsdfs.a
out/eloimx: out/integrators/libintegrators.a
out/eloimx: out/texture/libtexture.a
out/eloimx: out/render/librender.a
out/eloimx: out/core/libcore.a
out/eloimx: out/CMakeFiles/eloimx.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zcx/graphics/eloimx/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable eloimx"
	cd /home/zcx/graphics/eloimx/build/out && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eloimx.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
out/CMakeFiles/eloimx.dir/build: out/eloimx
.PHONY : out/CMakeFiles/eloimx.dir/build

out/CMakeFiles/eloimx.dir/clean:
	cd /home/zcx/graphics/eloimx/build/out && $(CMAKE_COMMAND) -P CMakeFiles/eloimx.dir/cmake_clean.cmake
.PHONY : out/CMakeFiles/eloimx.dir/clean

out/CMakeFiles/eloimx.dir/depend:
	cd /home/zcx/graphics/eloimx/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zcx/graphics/eloimx /home/zcx/graphics/eloimx/src /home/zcx/graphics/eloimx/build /home/zcx/graphics/eloimx/build/out /home/zcx/graphics/eloimx/build/out/CMakeFiles/eloimx.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : out/CMakeFiles/eloimx.dir/depend

