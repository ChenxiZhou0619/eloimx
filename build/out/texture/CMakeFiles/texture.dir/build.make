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
include out/texture/CMakeFiles/texture.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include out/texture/CMakeFiles/texture.dir/compiler_depend.make

# Include the progress variables for this target.
include out/texture/CMakeFiles/texture.dir/progress.make

# Include the compile flags for this target's objects.
include out/texture/CMakeFiles/texture.dir/flags.make

out/texture/CMakeFiles/texture.dir/bitmap.cpp.o: out/texture/CMakeFiles/texture.dir/flags.make
out/texture/CMakeFiles/texture.dir/bitmap.cpp.o: ../src/texture/bitmap.cpp
out/texture/CMakeFiles/texture.dir/bitmap.cpp.o: out/texture/CMakeFiles/texture.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zcx/graphics/eloimx/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object out/texture/CMakeFiles/texture.dir/bitmap.cpp.o"
	cd /home/zcx/graphics/eloimx/build/out/texture && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT out/texture/CMakeFiles/texture.dir/bitmap.cpp.o -MF CMakeFiles/texture.dir/bitmap.cpp.o.d -o CMakeFiles/texture.dir/bitmap.cpp.o -c /home/zcx/graphics/eloimx/src/texture/bitmap.cpp

out/texture/CMakeFiles/texture.dir/bitmap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/texture.dir/bitmap.cpp.i"
	cd /home/zcx/graphics/eloimx/build/out/texture && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zcx/graphics/eloimx/src/texture/bitmap.cpp > CMakeFiles/texture.dir/bitmap.cpp.i

out/texture/CMakeFiles/texture.dir/bitmap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/texture.dir/bitmap.cpp.s"
	cd /home/zcx/graphics/eloimx/build/out/texture && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zcx/graphics/eloimx/src/texture/bitmap.cpp -o CMakeFiles/texture.dir/bitmap.cpp.s

out/texture/CMakeFiles/texture.dir/constmap.cpp.o: out/texture/CMakeFiles/texture.dir/flags.make
out/texture/CMakeFiles/texture.dir/constmap.cpp.o: ../src/texture/constmap.cpp
out/texture/CMakeFiles/texture.dir/constmap.cpp.o: out/texture/CMakeFiles/texture.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zcx/graphics/eloimx/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object out/texture/CMakeFiles/texture.dir/constmap.cpp.o"
	cd /home/zcx/graphics/eloimx/build/out/texture && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT out/texture/CMakeFiles/texture.dir/constmap.cpp.o -MF CMakeFiles/texture.dir/constmap.cpp.o.d -o CMakeFiles/texture.dir/constmap.cpp.o -c /home/zcx/graphics/eloimx/src/texture/constmap.cpp

out/texture/CMakeFiles/texture.dir/constmap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/texture.dir/constmap.cpp.i"
	cd /home/zcx/graphics/eloimx/build/out/texture && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zcx/graphics/eloimx/src/texture/constmap.cpp > CMakeFiles/texture.dir/constmap.cpp.i

out/texture/CMakeFiles/texture.dir/constmap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/texture.dir/constmap.cpp.s"
	cd /home/zcx/graphics/eloimx/build/out/texture && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zcx/graphics/eloimx/src/texture/constmap.cpp -o CMakeFiles/texture.dir/constmap.cpp.s

# Object files for target texture
texture_OBJECTS = \
"CMakeFiles/texture.dir/bitmap.cpp.o" \
"CMakeFiles/texture.dir/constmap.cpp.o"

# External object files for target texture
texture_EXTERNAL_OBJECTS =

out/texture/libtexture.a: out/texture/CMakeFiles/texture.dir/bitmap.cpp.o
out/texture/libtexture.a: out/texture/CMakeFiles/texture.dir/constmap.cpp.o
out/texture/libtexture.a: out/texture/CMakeFiles/texture.dir/build.make
out/texture/libtexture.a: out/texture/CMakeFiles/texture.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zcx/graphics/eloimx/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libtexture.a"
	cd /home/zcx/graphics/eloimx/build/out/texture && $(CMAKE_COMMAND) -P CMakeFiles/texture.dir/cmake_clean_target.cmake
	cd /home/zcx/graphics/eloimx/build/out/texture && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/texture.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
out/texture/CMakeFiles/texture.dir/build: out/texture/libtexture.a
.PHONY : out/texture/CMakeFiles/texture.dir/build

out/texture/CMakeFiles/texture.dir/clean:
	cd /home/zcx/graphics/eloimx/build/out/texture && $(CMAKE_COMMAND) -P CMakeFiles/texture.dir/cmake_clean.cmake
.PHONY : out/texture/CMakeFiles/texture.dir/clean

out/texture/CMakeFiles/texture.dir/depend:
	cd /home/zcx/graphics/eloimx/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zcx/graphics/eloimx /home/zcx/graphics/eloimx/src/texture /home/zcx/graphics/eloimx/build /home/zcx/graphics/eloimx/build/out/texture /home/zcx/graphics/eloimx/build/out/texture/CMakeFiles/texture.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : out/texture/CMakeFiles/texture.dir/depend

