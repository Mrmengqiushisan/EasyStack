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
include examples/asio/chat/CMakeFiles/asio_chat_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/asio/chat/CMakeFiles/asio_chat_server.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/asio/chat/CMakeFiles/asio_chat_server.dir/progress.make

# Include the compile flags for this target's objects.
include examples/asio/chat/CMakeFiles/asio_chat_server.dir/flags.make

examples/asio/chat/CMakeFiles/asio_chat_server.dir/server.cc.o: examples/asio/chat/CMakeFiles/asio_chat_server.dir/flags.make
examples/asio/chat/CMakeFiles/asio_chat_server.dir/server.cc.o: /home/wangtao/easy_server/muduo-master/examples/asio/chat/server.cc
examples/asio/chat/CMakeFiles/asio_chat_server.dir/server.cc.o: examples/asio/chat/CMakeFiles/asio_chat_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangtao/easy_server/build/release-cpp11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/asio/chat/CMakeFiles/asio_chat_server.dir/server.cc.o"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/asio/chat && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/asio/chat/CMakeFiles/asio_chat_server.dir/server.cc.o -MF CMakeFiles/asio_chat_server.dir/server.cc.o.d -o CMakeFiles/asio_chat_server.dir/server.cc.o -c /home/wangtao/easy_server/muduo-master/examples/asio/chat/server.cc

examples/asio/chat/CMakeFiles/asio_chat_server.dir/server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/asio_chat_server.dir/server.cc.i"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/asio/chat && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangtao/easy_server/muduo-master/examples/asio/chat/server.cc > CMakeFiles/asio_chat_server.dir/server.cc.i

examples/asio/chat/CMakeFiles/asio_chat_server.dir/server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/asio_chat_server.dir/server.cc.s"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/asio/chat && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangtao/easy_server/muduo-master/examples/asio/chat/server.cc -o CMakeFiles/asio_chat_server.dir/server.cc.s

# Object files for target asio_chat_server
asio_chat_server_OBJECTS = \
"CMakeFiles/asio_chat_server.dir/server.cc.o"

# External object files for target asio_chat_server
asio_chat_server_EXTERNAL_OBJECTS =

bin/asio_chat_server: examples/asio/chat/CMakeFiles/asio_chat_server.dir/server.cc.o
bin/asio_chat_server: examples/asio/chat/CMakeFiles/asio_chat_server.dir/build.make
bin/asio_chat_server: lib/libmuduo_net.a
bin/asio_chat_server: lib/libmuduo_base.a
bin/asio_chat_server: examples/asio/chat/CMakeFiles/asio_chat_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wangtao/easy_server/build/release-cpp11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/asio_chat_server"
	cd /home/wangtao/easy_server/build/release-cpp11/examples/asio/chat && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/asio_chat_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/asio/chat/CMakeFiles/asio_chat_server.dir/build: bin/asio_chat_server
.PHONY : examples/asio/chat/CMakeFiles/asio_chat_server.dir/build

examples/asio/chat/CMakeFiles/asio_chat_server.dir/clean:
	cd /home/wangtao/easy_server/build/release-cpp11/examples/asio/chat && $(CMAKE_COMMAND) -P CMakeFiles/asio_chat_server.dir/cmake_clean.cmake
.PHONY : examples/asio/chat/CMakeFiles/asio_chat_server.dir/clean

examples/asio/chat/CMakeFiles/asio_chat_server.dir/depend:
	cd /home/wangtao/easy_server/build/release-cpp11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wangtao/easy_server/muduo-master /home/wangtao/easy_server/muduo-master/examples/asio/chat /home/wangtao/easy_server/build/release-cpp11 /home/wangtao/easy_server/build/release-cpp11/examples/asio/chat /home/wangtao/easy_server/build/release-cpp11/examples/asio/chat/CMakeFiles/asio_chat_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/asio/chat/CMakeFiles/asio_chat_server.dir/depend

