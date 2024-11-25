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
include examples/ace/logging/CMakeFiles/ace_logging_client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/ace/logging/CMakeFiles/ace_logging_client.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/ace/logging/CMakeFiles/ace_logging_client.dir/progress.make

# Include the compile flags for this target's objects.
include examples/ace/logging/CMakeFiles/ace_logging_client.dir/flags.make

examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o: examples/ace/logging/CMakeFiles/ace_logging_client.dir/flags.make
examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o: /home/wangtao/easy_server/muduo-master/examples/ace/logging/client.cc
examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o: examples/ace/logging/CMakeFiles/ace_logging_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangtao/easy_server/build/release-cpp11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/ace/logging && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o -MF CMakeFiles/ace_logging_client.dir/client.cc.o.d -o CMakeFiles/ace_logging_client.dir/client.cc.o -c /home/wangtao/easy_server/muduo-master/examples/ace/logging/client.cc

examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ace_logging_client.dir/client.cc.i"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/ace/logging && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangtao/easy_server/muduo-master/examples/ace/logging/client.cc > CMakeFiles/ace_logging_client.dir/client.cc.i

examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ace_logging_client.dir/client.cc.s"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/ace/logging && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangtao/easy_server/muduo-master/examples/ace/logging/client.cc -o CMakeFiles/ace_logging_client.dir/client.cc.s

# Object files for target ace_logging_client
ace_logging_client_OBJECTS = \
"CMakeFiles/ace_logging_client.dir/client.cc.o"

# External object files for target ace_logging_client
ace_logging_client_EXTERNAL_OBJECTS =

bin/ace_logging_client: examples/ace/logging/CMakeFiles/ace_logging_client.dir/client.cc.o
bin/ace_logging_client: examples/ace/logging/CMakeFiles/ace_logging_client.dir/build.make
bin/ace_logging_client: lib/libmuduo_protobuf_codec.a
bin/ace_logging_client: lib/libace_logging_proto.a
bin/ace_logging_client: lib/libmuduo_net.a
bin/ace_logging_client: lib/libmuduo_base.a
bin/ace_logging_client: examples/ace/logging/CMakeFiles/ace_logging_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wangtao/easy_server/build/release-cpp11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/ace_logging_client"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/ace/logging && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ace_logging_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/ace/logging/CMakeFiles/ace_logging_client.dir/build: bin/ace_logging_client
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_client.dir/build

examples/ace/logging/CMakeFiles/ace_logging_client.dir/clean:
	cd /home/wangtao/easy_server/build/release-cpp11/examples/ace/logging && $(CMAKE_COMMAND) -P CMakeFiles/ace_logging_client.dir/cmake_clean.cmake
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_client.dir/clean

examples/ace/logging/CMakeFiles/ace_logging_client.dir/depend:
	cd /home/wangtao/easy_server/build/release-cpp11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wangtao/easy_server/muduo-master /home/wangtao/easy_server/muduo-master/examples/ace/logging /home/wangtao/easy_server/build/release-cpp11 /home/wangtao/easy_server/build/release-cpp11/examples/ace/logging /home/wangtao/easy_server/build/release-cpp11/examples/ace/logging/CMakeFiles/ace_logging_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/ace/logging/CMakeFiles/ace_logging_client.dir/depend

