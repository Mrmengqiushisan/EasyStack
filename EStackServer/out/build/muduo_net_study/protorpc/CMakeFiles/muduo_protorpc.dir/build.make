# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/wangtao/easy_server/EStackServer/EStackServer/net

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study

# Include any dependencies generated for this target.
include protorpc/CMakeFiles/muduo_protorpc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include protorpc/CMakeFiles/muduo_protorpc.dir/compiler_depend.make

# Include the progress variables for this target.
include protorpc/CMakeFiles/muduo_protorpc.dir/progress.make

# Include the compile flags for this target's objects.
include protorpc/CMakeFiles/muduo_protorpc.dir/flags.make

protorpc/CMakeFiles/muduo_protorpc.dir/RpcChannel.o: protorpc/CMakeFiles/muduo_protorpc.dir/flags.make
protorpc/CMakeFiles/muduo_protorpc.dir/RpcChannel.o: /home/wangtao/easy_server/EStackServer/EStackServer/net/protorpc/RpcChannel.cc
protorpc/CMakeFiles/muduo_protorpc.dir/RpcChannel.o: protorpc/CMakeFiles/muduo_protorpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object protorpc/CMakeFiles/muduo_protorpc.dir/RpcChannel.o"
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/protorpc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT protorpc/CMakeFiles/muduo_protorpc.dir/RpcChannel.o -MF CMakeFiles/muduo_protorpc.dir/RpcChannel.o.d -o CMakeFiles/muduo_protorpc.dir/RpcChannel.o -c /home/wangtao/easy_server/EStackServer/EStackServer/net/protorpc/RpcChannel.cc

protorpc/CMakeFiles/muduo_protorpc.dir/RpcChannel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/muduo_protorpc.dir/RpcChannel.i"
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/protorpc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangtao/easy_server/EStackServer/EStackServer/net/protorpc/RpcChannel.cc > CMakeFiles/muduo_protorpc.dir/RpcChannel.i

protorpc/CMakeFiles/muduo_protorpc.dir/RpcChannel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/muduo_protorpc.dir/RpcChannel.s"
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/protorpc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangtao/easy_server/EStackServer/EStackServer/net/protorpc/RpcChannel.cc -o CMakeFiles/muduo_protorpc.dir/RpcChannel.s

protorpc/CMakeFiles/muduo_protorpc.dir/RpcServer.o: protorpc/CMakeFiles/muduo_protorpc.dir/flags.make
protorpc/CMakeFiles/muduo_protorpc.dir/RpcServer.o: /home/wangtao/easy_server/EStackServer/EStackServer/net/protorpc/RpcServer.cc
protorpc/CMakeFiles/muduo_protorpc.dir/RpcServer.o: protorpc/CMakeFiles/muduo_protorpc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object protorpc/CMakeFiles/muduo_protorpc.dir/RpcServer.o"
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/protorpc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT protorpc/CMakeFiles/muduo_protorpc.dir/RpcServer.o -MF CMakeFiles/muduo_protorpc.dir/RpcServer.o.d -o CMakeFiles/muduo_protorpc.dir/RpcServer.o -c /home/wangtao/easy_server/EStackServer/EStackServer/net/protorpc/RpcServer.cc

protorpc/CMakeFiles/muduo_protorpc.dir/RpcServer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/muduo_protorpc.dir/RpcServer.i"
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/protorpc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangtao/easy_server/EStackServer/EStackServer/net/protorpc/RpcServer.cc > CMakeFiles/muduo_protorpc.dir/RpcServer.i

protorpc/CMakeFiles/muduo_protorpc.dir/RpcServer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/muduo_protorpc.dir/RpcServer.s"
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/protorpc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangtao/easy_server/EStackServer/EStackServer/net/protorpc/RpcServer.cc -o CMakeFiles/muduo_protorpc.dir/RpcServer.s

# Object files for target muduo_protorpc
muduo_protorpc_OBJECTS = \
"CMakeFiles/muduo_protorpc.dir/RpcChannel.o" \
"CMakeFiles/muduo_protorpc.dir/RpcServer.o"

# External object files for target muduo_protorpc
muduo_protorpc_EXTERNAL_OBJECTS =

protorpc/libmuduo_protorpc.a: protorpc/CMakeFiles/muduo_protorpc.dir/RpcChannel.o
protorpc/libmuduo_protorpc.a: protorpc/CMakeFiles/muduo_protorpc.dir/RpcServer.o
protorpc/libmuduo_protorpc.a: protorpc/CMakeFiles/muduo_protorpc.dir/build.make
protorpc/libmuduo_protorpc.a: protorpc/CMakeFiles/muduo_protorpc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libmuduo_protorpc.a"
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/protorpc && $(CMAKE_COMMAND) -P CMakeFiles/muduo_protorpc.dir/cmake_clean_target.cmake
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/protorpc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/muduo_protorpc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
protorpc/CMakeFiles/muduo_protorpc.dir/build: protorpc/libmuduo_protorpc.a
.PHONY : protorpc/CMakeFiles/muduo_protorpc.dir/build

protorpc/CMakeFiles/muduo_protorpc.dir/clean:
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/protorpc && $(CMAKE_COMMAND) -P CMakeFiles/muduo_protorpc.dir/cmake_clean.cmake
.PHONY : protorpc/CMakeFiles/muduo_protorpc.dir/clean

protorpc/CMakeFiles/muduo_protorpc.dir/depend:
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wangtao/easy_server/EStackServer/EStackServer/net /home/wangtao/easy_server/EStackServer/EStackServer/net/protorpc /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/protorpc /home/wangtao/easy_server/EStackServer/out/build/muduo_net_study/protorpc/CMakeFiles/muduo_protorpc.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : protorpc/CMakeFiles/muduo_protorpc.dir/depend

