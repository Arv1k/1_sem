# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/arv1k/CLion/clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/arv1k/CLion/clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arv1k/CLionProjects/1_sem/List/for_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arv1k/CLionProjects/1_sem/List/for_test/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/for_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/for_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/for_test.dir/flags.make

CMakeFiles/for_test.dir/main.c.o: CMakeFiles/for_test.dir/flags.make
CMakeFiles/for_test.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arv1k/CLionProjects/1_sem/List/for_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/for_test.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/for_test.dir/main.c.o   -c /home/arv1k/CLionProjects/1_sem/List/for_test/main.c

CMakeFiles/for_test.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/for_test.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/arv1k/CLionProjects/1_sem/List/for_test/main.c > CMakeFiles/for_test.dir/main.c.i

CMakeFiles/for_test.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/for_test.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/arv1k/CLionProjects/1_sem/List/for_test/main.c -o CMakeFiles/for_test.dir/main.c.s

# Object files for target for_test
for_test_OBJECTS = \
"CMakeFiles/for_test.dir/main.c.o"

# External object files for target for_test
for_test_EXTERNAL_OBJECTS =

for_test: CMakeFiles/for_test.dir/main.c.o
for_test: CMakeFiles/for_test.dir/build.make
for_test: CMakeFiles/for_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arv1k/CLionProjects/1_sem/List/for_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable for_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/for_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/for_test.dir/build: for_test

.PHONY : CMakeFiles/for_test.dir/build

CMakeFiles/for_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/for_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/for_test.dir/clean

CMakeFiles/for_test.dir/depend:
	cd /home/arv1k/CLionProjects/1_sem/List/for_test/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arv1k/CLionProjects/1_sem/List/for_test /home/arv1k/CLionProjects/1_sem/List/for_test /home/arv1k/CLionProjects/1_sem/List/for_test/cmake-build-debug /home/arv1k/CLionProjects/1_sem/List/for_test/cmake-build-debug /home/arv1k/CLionProjects/1_sem/List/for_test/cmake-build-debug/CMakeFiles/for_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/for_test.dir/depend
