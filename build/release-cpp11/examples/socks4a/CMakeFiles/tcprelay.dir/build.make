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
include examples/socks4a/CMakeFiles/tcprelay.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/socks4a/CMakeFiles/tcprelay.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/socks4a/CMakeFiles/tcprelay.dir/progress.make

# Include the compile flags for this target's objects.
include examples/socks4a/CMakeFiles/tcprelay.dir/flags.make

examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o: examples/socks4a/CMakeFiles/tcprelay.dir/flags.make
examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o: /home/wangtao/easy_server/muduo-master/examples/socks4a/tcprelay.cc
examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o: examples/socks4a/CMakeFiles/tcprelay.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangtao/easy_server/build/release-cpp11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/socks4a && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o -MF CMakeFiles/tcprelay.dir/tcprelay.cc.o.d -o CMakeFiles/tcprelay.dir/tcprelay.cc.o -c /home/wangtao/easy_server/muduo-master/examples/socks4a/tcprelay.cc

examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcprelay.dir/tcprelay.cc.i"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/socks4a && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangtao/easy_server/muduo-master/examples/socks4a/tcprelay.cc > CMakeFiles/tcprelay.dir/tcprelay.cc.i

examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcprelay.dir/tcprelay.cc.s"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/socks4a && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangtao/easy_server/muduo-master/examples/socks4a/tcprelay.cc -o CMakeFiles/tcprelay.dir/tcprelay.cc.s

# Object files for target tcprelay
tcprelay_OBJECTS = \
"CMakeFiles/tcprelay.dir/tcprelay.cc.o"

# External object files for target tcprelay
tcprelay_EXTERNAL_OBJECTS =

bin/tcprelay: examples/socks4a/CMakeFiles/tcprelay.dir/tcprelay.cc.o
bin/tcprelay: examples/socks4a/CMakeFiles/tcprelay.dir/build.make
bin/tcprelay: lib/libmuduo_net.a
bin/tcprelay: lib/libmuduo_base.a
bin/tcprelay: examples/socks4a/CMakeFiles/tcprelay.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wangtao/easy_server/build/release-cpp11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/tcprelay"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/socks4a && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcprelay.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/socks4a/CMakeFiles/tcprelay.dir/build: bin/tcprelay
.PHONY : examples/socks4a/CMakeFiles/tcprelay.dir/build

examples/socks4a/CMakeFiles/tcprelay.dir/clean:
	cd /home/wangtao/easy_server/build/release-cpp11/examples/socks4a && $(CMAKE_COMMAND) -P CMakeFiles/tcprelay.dir/cmake_clean.cmake
.PHONY : examples/socks4a/CMakeFiles/tcprelay.dir/clean

examples/socks4a/CMakeFiles/tcprelay.dir/depend:
	cd /home/wangtao/easy_server/build/release-cpp11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wangtao/easy_server/muduo-master /home/wangtao/easy_server/muduo-master/examples/socks4a /home/wangtao/easy_server/build/release-cpp11 /home/wangtao/easy_server/build/release-cpp11/examples/socks4a /home/wangtao/easy_server/build/release-cpp11/examples/socks4a/CMakeFiles/tcprelay.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/socks4a/CMakeFiles/tcprelay.dir/depend

