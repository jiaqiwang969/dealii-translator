# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /home/runner/work/dealii-translator/dealii-translator/dealii

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/runner/work/dealii-translator/dealii-translator/dealii

# Utility rule file for tutorial_step-20.

# Include any custom commands dependencies for this target.
include doc/doxygen/tutorial/CMakeFiles/tutorial_step-20.dir/compiler_depend.make

# Include the progress variables for this target.
include doc/doxygen/tutorial/CMakeFiles/tutorial_step-20.dir/progress.make

doc/doxygen/tutorial/CMakeFiles/tutorial_step-20: doc/doxygen/tutorial/step-20.h
doc/doxygen/tutorial/CMakeFiles/tutorial_step-20: doc/doxygen/tutorial/step-20.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/runner/work/dealii-translator/dealii-translator/dealii/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building doxygen input file for tutorial program <step-20>"

doc/doxygen/tutorial/step-20.cc: doc/doxygen/scripts/program2plain
doc/doxygen/tutorial/step-20.cc: examples/step-20/step-20.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/runner/work/dealii-translator/dealii-translator/dealii/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating step-20.cc"
	cd /home/runner/work/dealii-translator/dealii-translator/dealii/doc/doxygen/tutorial && /usr/bin/perl /home/runner/work/dealii-translator/dealii-translator/dealii/doc/doxygen/scripts/program2plain < /home/runner/work/dealii-translator/dealii-translator/dealii/examples/step-20/step-20.cc > /home/runner/work/dealii-translator/dealii-translator/dealii/doc/doxygen/tutorial/step-20.cc

doc/doxygen/tutorial/step-20.h: doc/doxygen/scripts/make_step.pl
doc/doxygen/tutorial/step-20.h: doc/doxygen/scripts/intro2toc
doc/doxygen/tutorial/step-20.h: doc/doxygen/scripts/create_anchors
doc/doxygen/tutorial/step-20.h: doc/doxygen/scripts/program2doxygen
doc/doxygen/tutorial/step-20.h: examples/step-20/step-20.cc
doc/doxygen/tutorial/step-20.h: examples/step-20/doc/intro.dox
doc/doxygen/tutorial/step-20.h: examples/step-20/doc/results.dox
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/runner/work/dealii-translator/dealii-translator/dealii/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating step-20.h"
	cd /home/runner/work/dealii-translator/dealii-translator/dealii/doc/doxygen/tutorial && /usr/bin/perl /home/runner/work/dealii-translator/dealii-translator/dealii/doc/doxygen/scripts/make_step.pl step-20 /home/runner/work/dealii-translator/dealii-translator/dealii > /home/runner/work/dealii-translator/dealii-translator/dealii/doc/doxygen/tutorial/step-20.h

tutorial_step-20: doc/doxygen/tutorial/CMakeFiles/tutorial_step-20
tutorial_step-20: doc/doxygen/tutorial/step-20.cc
tutorial_step-20: doc/doxygen/tutorial/step-20.h
tutorial_step-20: doc/doxygen/tutorial/CMakeFiles/tutorial_step-20.dir/build.make
.PHONY : tutorial_step-20

# Rule to build all files generated by this target.
doc/doxygen/tutorial/CMakeFiles/tutorial_step-20.dir/build: tutorial_step-20
.PHONY : doc/doxygen/tutorial/CMakeFiles/tutorial_step-20.dir/build

doc/doxygen/tutorial/CMakeFiles/tutorial_step-20.dir/clean:
	cd /home/runner/work/dealii-translator/dealii-translator/dealii/doc/doxygen/tutorial && $(CMAKE_COMMAND) -P CMakeFiles/tutorial_step-20.dir/cmake_clean.cmake
.PHONY : doc/doxygen/tutorial/CMakeFiles/tutorial_step-20.dir/clean

doc/doxygen/tutorial/CMakeFiles/tutorial_step-20.dir/depend:
	cd /home/runner/work/dealii-translator/dealii-translator/dealii && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/runner/work/dealii-translator/dealii-translator/dealii /home/runner/work/dealii-translator/dealii-translator/dealii/doc/doxygen/tutorial /home/runner/work/dealii-translator/dealii-translator/dealii /home/runner/work/dealii-translator/dealii-translator/dealii/doc/doxygen/tutorial /home/runner/work/dealii-translator/dealii-translator/dealii/doc/doxygen/tutorial/CMakeFiles/tutorial_step-20.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/doxygen/tutorial/CMakeFiles/tutorial_step-20.dir/depend

