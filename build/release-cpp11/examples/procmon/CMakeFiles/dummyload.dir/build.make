# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wangtao/easy_server/muduo-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wangtao/easy_server/build/release-cpp11

# Include any dependencies generated for this target.
include examples/procmon/CMakeFiles/dummyload.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/procmon/CMakeFiles/dummyload.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/procmon/CMakeFiles/dummyload.dir/progress.make

# Include the compile flags for this target's objects.
include examples/procmon/CMakeFiles/dummyload.dir/flags.make

examples/procmon/CMakeFiles/dummyload.dir/dummyload.cc.o: examples/procmon/CMakeFiles/dummyload.dir/flags.make
examples/procmon/CMakeFiles/dummyload.dir/dummyload.cc.o: /home/wangtao/easy_server/muduo-master/examples/procmon/dummyload.cc
examples/procmon/CMakeFiles/dummyload.dir/dummyload.cc.o: examples/procmon/CMakeFiles/dummyload.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangtao/easy_server/build/release-cpp11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/procmon/CMakeFiles/dummyload.dir/dummyload.cc.o"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/procmon && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/procmon/CMakeFiles/dummyload.dir/dummyload.cc.o -MF CMakeFiles/dummyload.dir/dummyload.cc.o.d -o CMakeFiles/dummyload.dir/dummyload.cc.o -c /home/wangtao/easy_server/muduo-master/examples/procmon/dummyload.cc

examples/procmon/CMakeFiles/dummyload.dir/dummyload.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dummyload.dir/dummyload.cc.i"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/procmon && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangtao/easy_server/muduo-master/examples/procmon/dummyload.cc > CMakeFiles/dummyload.dir/dummyload.cc.i

examples/procmon/CMakeFiles/dummyload.dir/dummyload.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dummyload.dir/dummyload.cc.s"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/procmon && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangtao/easy_server/muduo-master/examples/procmon/dummyload.cc -o CMakeFiles/dummyload.dir/dummyload.cc.s

# Object files for target dummyload
dummyload_OBJECTS = \
"CMakeFiles/dummyload.dir/dummyload.cc.o"

# External object files for target dummyload
dummyload_EXTERNAL_OBJECTS =

bin/dummyload: examples/procmon/CMakeFiles/dummyload.dir/dummyload.cc.o
bin/dummyload: examples/procmon/CMakeFiles/dummyload.dir/build.make
bin/dummyload: lib/libmuduo_net.a
bin/dummyload: lib/libmuduo_base.a
bin/dummyload: examples/procmon/CMakeFiles/dummyload.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wangtao/easy_server/build/release-cpp11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/dummyload"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/procmon && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dummyload.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/procmon/CMakeFiles/dummyload.dir/build: bin/dummyload
.PHONY : examples/procmon/CMakeFiles/dummyload.dir/build

examples/procmon/CMakeFiles/dummyload.dir/clean:
	cd /home/wangtao/easy_server/build/release-cpp11/examples/procmon && $(CMAKE_COMMAND) -P CMakeFiles/dummyload.dir/cmake_clean.cmake
.PHONY : examples/procmon/CMakeFiles/dummyload.dir/clean

examples/procmon/CMakeFiles/dummyload.dir/depend:
	cd /home/wangtao/easy_server/build/release-cpp11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wangtao/easy_server/muduo-master /home/wangtao/easy_server/muduo-master/examples/procmon /home/wangtao/easy_server/build/release-cpp11 /home/wangtao/easy_server/build/release-cpp11/examples/procmon /home/wangtao/easy_server/build/release-cpp11/examples/procmon/CMakeFiles/dummyload.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/procmon/CMakeFiles/dummyload.dir/depend

