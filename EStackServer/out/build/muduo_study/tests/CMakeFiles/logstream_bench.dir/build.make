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
CMAKE_SOURCE_DIR = /home/wangtao/easy_server/EStackServer/EStackServer/base

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wangtao/easy_server/EStackServer/out/build/muduo_study

# Include any dependencies generated for this target.
include tests/CMakeFiles/logstream_bench.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/logstream_bench.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/logstream_bench.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/logstream_bench.dir/flags.make

tests/CMakeFiles/logstream_bench.dir/LogStream_bench.cc.o: tests/CMakeFiles/logstream_bench.dir/flags.make
tests/CMakeFiles/logstream_bench.dir/LogStream_bench.cc.o: /home/wangtao/easy_server/EStackServer/EStackServer/base/tests/LogStream_bench.cc
tests/CMakeFiles/logstream_bench.dir/LogStream_bench.cc.o: tests/CMakeFiles/logstream_bench.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/wangtao/easy_server/EStackServer/out/build/muduo_study/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/logstream_bench.dir/LogStream_bench.cc.o"
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_study/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/logstream_bench.dir/LogStream_bench.cc.o -MF CMakeFiles/logstream_bench.dir/LogStream_bench.cc.o.d -o CMakeFiles/logstream_bench.dir/LogStream_bench.cc.o -c /home/wangtao/easy_server/EStackServer/EStackServer/base/tests/LogStream_bench.cc

tests/CMakeFiles/logstream_bench.dir/LogStream_bench.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/logstream_bench.dir/LogStream_bench.cc.i"
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_study/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangtao/easy_server/EStackServer/EStackServer/base/tests/LogStream_bench.cc > CMakeFiles/logstream_bench.dir/LogStream_bench.cc.i

tests/CMakeFiles/logstream_bench.dir/LogStream_bench.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/logstream_bench.dir/LogStream_bench.cc.s"
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_study/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangtao/easy_server/EStackServer/EStackServer/base/tests/LogStream_bench.cc -o CMakeFiles/logstream_bench.dir/LogStream_bench.cc.s

# Object files for target logstream_bench
logstream_bench_OBJECTS = \
"CMakeFiles/logstream_bench.dir/LogStream_bench.cc.o"

# External object files for target logstream_bench
logstream_bench_EXTERNAL_OBJECTS =

tests/logstream_bench: tests/CMakeFiles/logstream_bench.dir/LogStream_bench.cc.o
tests/logstream_bench: tests/CMakeFiles/logstream_bench.dir/build.make
tests/logstream_bench: libmuduo_base.a
tests/logstream_bench: tests/CMakeFiles/logstream_bench.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/wangtao/easy_server/EStackServer/out/build/muduo_study/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable logstream_bench"
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_study/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/logstream_bench.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/logstream_bench.dir/build: tests/logstream_bench
.PHONY : tests/CMakeFiles/logstream_bench.dir/build

tests/CMakeFiles/logstream_bench.dir/clean:
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_study/tests && $(CMAKE_COMMAND) -P CMakeFiles/logstream_bench.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/logstream_bench.dir/clean

tests/CMakeFiles/logstream_bench.dir/depend:
	cd /home/wangtao/easy_server/EStackServer/out/build/muduo_study && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wangtao/easy_server/EStackServer/EStackServer/base /home/wangtao/easy_server/EStackServer/EStackServer/base/tests /home/wangtao/easy_server/EStackServer/out/build/muduo_study /home/wangtao/easy_server/EStackServer/out/build/muduo_study/tests /home/wangtao/easy_server/EStackServer/out/build/muduo_study/tests/CMakeFiles/logstream_bench.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/logstream_bench.dir/depend
