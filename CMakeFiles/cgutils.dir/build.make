# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tim/workspace/cg-utils

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tim/workspace/cg-utils

# Include any dependencies generated for this target.
include CMakeFiles/cgutils.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cgutils.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cgutils.dir/flags.make

CMakeFiles/cgutils.dir/src/mesh.cpp.o: CMakeFiles/cgutils.dir/flags.make
CMakeFiles/cgutils.dir/src/mesh.cpp.o: src/mesh.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tim/workspace/cg-utils/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cgutils.dir/src/mesh.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cgutils.dir/src/mesh.cpp.o -c /home/tim/workspace/cg-utils/src/mesh.cpp

CMakeFiles/cgutils.dir/src/mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgutils.dir/src/mesh.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tim/workspace/cg-utils/src/mesh.cpp > CMakeFiles/cgutils.dir/src/mesh.cpp.i

CMakeFiles/cgutils.dir/src/mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgutils.dir/src/mesh.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tim/workspace/cg-utils/src/mesh.cpp -o CMakeFiles/cgutils.dir/src/mesh.cpp.s

CMakeFiles/cgutils.dir/src/mesh.cpp.o.requires:
.PHONY : CMakeFiles/cgutils.dir/src/mesh.cpp.o.requires

CMakeFiles/cgutils.dir/src/mesh.cpp.o.provides: CMakeFiles/cgutils.dir/src/mesh.cpp.o.requires
	$(MAKE) -f CMakeFiles/cgutils.dir/build.make CMakeFiles/cgutils.dir/src/mesh.cpp.o.provides.build
.PHONY : CMakeFiles/cgutils.dir/src/mesh.cpp.o.provides

CMakeFiles/cgutils.dir/src/mesh.cpp.o.provides.build: CMakeFiles/cgutils.dir/src/mesh.cpp.o

CMakeFiles/cgutils.dir/src/aabb.cpp.o: CMakeFiles/cgutils.dir/flags.make
CMakeFiles/cgutils.dir/src/aabb.cpp.o: src/aabb.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tim/workspace/cg-utils/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cgutils.dir/src/aabb.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cgutils.dir/src/aabb.cpp.o -c /home/tim/workspace/cg-utils/src/aabb.cpp

CMakeFiles/cgutils.dir/src/aabb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgutils.dir/src/aabb.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tim/workspace/cg-utils/src/aabb.cpp > CMakeFiles/cgutils.dir/src/aabb.cpp.i

CMakeFiles/cgutils.dir/src/aabb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgutils.dir/src/aabb.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tim/workspace/cg-utils/src/aabb.cpp -o CMakeFiles/cgutils.dir/src/aabb.cpp.s

CMakeFiles/cgutils.dir/src/aabb.cpp.o.requires:
.PHONY : CMakeFiles/cgutils.dir/src/aabb.cpp.o.requires

CMakeFiles/cgutils.dir/src/aabb.cpp.o.provides: CMakeFiles/cgutils.dir/src/aabb.cpp.o.requires
	$(MAKE) -f CMakeFiles/cgutils.dir/build.make CMakeFiles/cgutils.dir/src/aabb.cpp.o.provides.build
.PHONY : CMakeFiles/cgutils.dir/src/aabb.cpp.o.provides

CMakeFiles/cgutils.dir/src/aabb.cpp.o.provides.build: CMakeFiles/cgutils.dir/src/aabb.cpp.o

CMakeFiles/cgutils.dir/src/ray.cpp.o: CMakeFiles/cgutils.dir/flags.make
CMakeFiles/cgutils.dir/src/ray.cpp.o: src/ray.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tim/workspace/cg-utils/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cgutils.dir/src/ray.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cgutils.dir/src/ray.cpp.o -c /home/tim/workspace/cg-utils/src/ray.cpp

CMakeFiles/cgutils.dir/src/ray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgutils.dir/src/ray.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tim/workspace/cg-utils/src/ray.cpp > CMakeFiles/cgutils.dir/src/ray.cpp.i

CMakeFiles/cgutils.dir/src/ray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgutils.dir/src/ray.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tim/workspace/cg-utils/src/ray.cpp -o CMakeFiles/cgutils.dir/src/ray.cpp.s

CMakeFiles/cgutils.dir/src/ray.cpp.o.requires:
.PHONY : CMakeFiles/cgutils.dir/src/ray.cpp.o.requires

CMakeFiles/cgutils.dir/src/ray.cpp.o.provides: CMakeFiles/cgutils.dir/src/ray.cpp.o.requires
	$(MAKE) -f CMakeFiles/cgutils.dir/build.make CMakeFiles/cgutils.dir/src/ray.cpp.o.provides.build
.PHONY : CMakeFiles/cgutils.dir/src/ray.cpp.o.provides

CMakeFiles/cgutils.dir/src/ray.cpp.o.provides.build: CMakeFiles/cgutils.dir/src/ray.cpp.o

CMakeFiles/cgutils.dir/src/texture.cpp.o: CMakeFiles/cgutils.dir/flags.make
CMakeFiles/cgutils.dir/src/texture.cpp.o: src/texture.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tim/workspace/cg-utils/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cgutils.dir/src/texture.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cgutils.dir/src/texture.cpp.o -c /home/tim/workspace/cg-utils/src/texture.cpp

CMakeFiles/cgutils.dir/src/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgutils.dir/src/texture.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tim/workspace/cg-utils/src/texture.cpp > CMakeFiles/cgutils.dir/src/texture.cpp.i

CMakeFiles/cgutils.dir/src/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgutils.dir/src/texture.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tim/workspace/cg-utils/src/texture.cpp -o CMakeFiles/cgutils.dir/src/texture.cpp.s

CMakeFiles/cgutils.dir/src/texture.cpp.o.requires:
.PHONY : CMakeFiles/cgutils.dir/src/texture.cpp.o.requires

CMakeFiles/cgutils.dir/src/texture.cpp.o.provides: CMakeFiles/cgutils.dir/src/texture.cpp.o.requires
	$(MAKE) -f CMakeFiles/cgutils.dir/build.make CMakeFiles/cgutils.dir/src/texture.cpp.o.provides.build
.PHONY : CMakeFiles/cgutils.dir/src/texture.cpp.o.provides

CMakeFiles/cgutils.dir/src/texture.cpp.o.provides.build: CMakeFiles/cgutils.dir/src/texture.cpp.o

CMakeFiles/cgutils.dir/src/light.cpp.o: CMakeFiles/cgutils.dir/flags.make
CMakeFiles/cgutils.dir/src/light.cpp.o: src/light.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tim/workspace/cg-utils/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cgutils.dir/src/light.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cgutils.dir/src/light.cpp.o -c /home/tim/workspace/cg-utils/src/light.cpp

CMakeFiles/cgutils.dir/src/light.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgutils.dir/src/light.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tim/workspace/cg-utils/src/light.cpp > CMakeFiles/cgutils.dir/src/light.cpp.i

CMakeFiles/cgutils.dir/src/light.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgutils.dir/src/light.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tim/workspace/cg-utils/src/light.cpp -o CMakeFiles/cgutils.dir/src/light.cpp.s

CMakeFiles/cgutils.dir/src/light.cpp.o.requires:
.PHONY : CMakeFiles/cgutils.dir/src/light.cpp.o.requires

CMakeFiles/cgutils.dir/src/light.cpp.o.provides: CMakeFiles/cgutils.dir/src/light.cpp.o.requires
	$(MAKE) -f CMakeFiles/cgutils.dir/build.make CMakeFiles/cgutils.dir/src/light.cpp.o.provides.build
.PHONY : CMakeFiles/cgutils.dir/src/light.cpp.o.provides

CMakeFiles/cgutils.dir/src/light.cpp.o.provides.build: CMakeFiles/cgutils.dir/src/light.cpp.o

CMakeFiles/cgutils.dir/src/common.cpp.o: CMakeFiles/cgutils.dir/flags.make
CMakeFiles/cgutils.dir/src/common.cpp.o: src/common.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tim/workspace/cg-utils/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cgutils.dir/src/common.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cgutils.dir/src/common.cpp.o -c /home/tim/workspace/cg-utils/src/common.cpp

CMakeFiles/cgutils.dir/src/common.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgutils.dir/src/common.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tim/workspace/cg-utils/src/common.cpp > CMakeFiles/cgutils.dir/src/common.cpp.i

CMakeFiles/cgutils.dir/src/common.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgutils.dir/src/common.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tim/workspace/cg-utils/src/common.cpp -o CMakeFiles/cgutils.dir/src/common.cpp.s

CMakeFiles/cgutils.dir/src/common.cpp.o.requires:
.PHONY : CMakeFiles/cgutils.dir/src/common.cpp.o.requires

CMakeFiles/cgutils.dir/src/common.cpp.o.provides: CMakeFiles/cgutils.dir/src/common.cpp.o.requires
	$(MAKE) -f CMakeFiles/cgutils.dir/build.make CMakeFiles/cgutils.dir/src/common.cpp.o.provides.build
.PHONY : CMakeFiles/cgutils.dir/src/common.cpp.o.provides

CMakeFiles/cgutils.dir/src/common.cpp.o.provides.build: CMakeFiles/cgutils.dir/src/common.cpp.o

CMakeFiles/cgutils.dir/src/entity.cpp.o: CMakeFiles/cgutils.dir/flags.make
CMakeFiles/cgutils.dir/src/entity.cpp.o: src/entity.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tim/workspace/cg-utils/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cgutils.dir/src/entity.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cgutils.dir/src/entity.cpp.o -c /home/tim/workspace/cg-utils/src/entity.cpp

CMakeFiles/cgutils.dir/src/entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgutils.dir/src/entity.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tim/workspace/cg-utils/src/entity.cpp > CMakeFiles/cgutils.dir/src/entity.cpp.i

CMakeFiles/cgutils.dir/src/entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgutils.dir/src/entity.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tim/workspace/cg-utils/src/entity.cpp -o CMakeFiles/cgutils.dir/src/entity.cpp.s

CMakeFiles/cgutils.dir/src/entity.cpp.o.requires:
.PHONY : CMakeFiles/cgutils.dir/src/entity.cpp.o.requires

CMakeFiles/cgutils.dir/src/entity.cpp.o.provides: CMakeFiles/cgutils.dir/src/entity.cpp.o.requires
	$(MAKE) -f CMakeFiles/cgutils.dir/build.make CMakeFiles/cgutils.dir/src/entity.cpp.o.provides.build
.PHONY : CMakeFiles/cgutils.dir/src/entity.cpp.o.provides

CMakeFiles/cgutils.dir/src/entity.cpp.o.provides.build: CMakeFiles/cgutils.dir/src/entity.cpp.o

CMakeFiles/cgutils.dir/src/material.cpp.o: CMakeFiles/cgutils.dir/flags.make
CMakeFiles/cgutils.dir/src/material.cpp.o: src/material.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tim/workspace/cg-utils/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cgutils.dir/src/material.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cgutils.dir/src/material.cpp.o -c /home/tim/workspace/cg-utils/src/material.cpp

CMakeFiles/cgutils.dir/src/material.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgutils.dir/src/material.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tim/workspace/cg-utils/src/material.cpp > CMakeFiles/cgutils.dir/src/material.cpp.i

CMakeFiles/cgutils.dir/src/material.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgutils.dir/src/material.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tim/workspace/cg-utils/src/material.cpp -o CMakeFiles/cgutils.dir/src/material.cpp.s

CMakeFiles/cgutils.dir/src/material.cpp.o.requires:
.PHONY : CMakeFiles/cgutils.dir/src/material.cpp.o.requires

CMakeFiles/cgutils.dir/src/material.cpp.o.provides: CMakeFiles/cgutils.dir/src/material.cpp.o.requires
	$(MAKE) -f CMakeFiles/cgutils.dir/build.make CMakeFiles/cgutils.dir/src/material.cpp.o.provides.build
.PHONY : CMakeFiles/cgutils.dir/src/material.cpp.o.provides

CMakeFiles/cgutils.dir/src/material.cpp.o.provides.build: CMakeFiles/cgutils.dir/src/material.cpp.o

CMakeFiles/cgutils.dir/src/camera.cpp.o: CMakeFiles/cgutils.dir/flags.make
CMakeFiles/cgutils.dir/src/camera.cpp.o: src/camera.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tim/workspace/cg-utils/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cgutils.dir/src/camera.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cgutils.dir/src/camera.cpp.o -c /home/tim/workspace/cg-utils/src/camera.cpp

CMakeFiles/cgutils.dir/src/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgutils.dir/src/camera.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tim/workspace/cg-utils/src/camera.cpp > CMakeFiles/cgutils.dir/src/camera.cpp.i

CMakeFiles/cgutils.dir/src/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgutils.dir/src/camera.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tim/workspace/cg-utils/src/camera.cpp -o CMakeFiles/cgutils.dir/src/camera.cpp.s

CMakeFiles/cgutils.dir/src/camera.cpp.o.requires:
.PHONY : CMakeFiles/cgutils.dir/src/camera.cpp.o.requires

CMakeFiles/cgutils.dir/src/camera.cpp.o.provides: CMakeFiles/cgutils.dir/src/camera.cpp.o.requires
	$(MAKE) -f CMakeFiles/cgutils.dir/build.make CMakeFiles/cgutils.dir/src/camera.cpp.o.provides.build
.PHONY : CMakeFiles/cgutils.dir/src/camera.cpp.o.provides

CMakeFiles/cgutils.dir/src/camera.cpp.o.provides.build: CMakeFiles/cgutils.dir/src/camera.cpp.o

CMakeFiles/cgutils.dir/src/resources.cpp.o: CMakeFiles/cgutils.dir/flags.make
CMakeFiles/cgutils.dir/src/resources.cpp.o: src/resources.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tim/workspace/cg-utils/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cgutils.dir/src/resources.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cgutils.dir/src/resources.cpp.o -c /home/tim/workspace/cg-utils/src/resources.cpp

CMakeFiles/cgutils.dir/src/resources.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgutils.dir/src/resources.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tim/workspace/cg-utils/src/resources.cpp > CMakeFiles/cgutils.dir/src/resources.cpp.i

CMakeFiles/cgutils.dir/src/resources.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgutils.dir/src/resources.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tim/workspace/cg-utils/src/resources.cpp -o CMakeFiles/cgutils.dir/src/resources.cpp.s

CMakeFiles/cgutils.dir/src/resources.cpp.o.requires:
.PHONY : CMakeFiles/cgutils.dir/src/resources.cpp.o.requires

CMakeFiles/cgutils.dir/src/resources.cpp.o.provides: CMakeFiles/cgutils.dir/src/resources.cpp.o.requires
	$(MAKE) -f CMakeFiles/cgutils.dir/build.make CMakeFiles/cgutils.dir/src/resources.cpp.o.provides.build
.PHONY : CMakeFiles/cgutils.dir/src/resources.cpp.o.provides

CMakeFiles/cgutils.dir/src/resources.cpp.o.provides.build: CMakeFiles/cgutils.dir/src/resources.cpp.o

CMakeFiles/cgutils.dir/src/rtimage.cpp.o: CMakeFiles/cgutils.dir/flags.make
CMakeFiles/cgutils.dir/src/rtimage.cpp.o: src/rtimage.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tim/workspace/cg-utils/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cgutils.dir/src/rtimage.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cgutils.dir/src/rtimage.cpp.o -c /home/tim/workspace/cg-utils/src/rtimage.cpp

CMakeFiles/cgutils.dir/src/rtimage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgutils.dir/src/rtimage.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tim/workspace/cg-utils/src/rtimage.cpp > CMakeFiles/cgutils.dir/src/rtimage.cpp.i

CMakeFiles/cgutils.dir/src/rtimage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgutils.dir/src/rtimage.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tim/workspace/cg-utils/src/rtimage.cpp -o CMakeFiles/cgutils.dir/src/rtimage.cpp.s

CMakeFiles/cgutils.dir/src/rtimage.cpp.o.requires:
.PHONY : CMakeFiles/cgutils.dir/src/rtimage.cpp.o.requires

CMakeFiles/cgutils.dir/src/rtimage.cpp.o.provides: CMakeFiles/cgutils.dir/src/rtimage.cpp.o.requires
	$(MAKE) -f CMakeFiles/cgutils.dir/build.make CMakeFiles/cgutils.dir/src/rtimage.cpp.o.provides.build
.PHONY : CMakeFiles/cgutils.dir/src/rtimage.cpp.o.provides

CMakeFiles/cgutils.dir/src/rtimage.cpp.o.provides.build: CMakeFiles/cgutils.dir/src/rtimage.cpp.o

# Object files for target cgutils
cgutils_OBJECTS = \
"CMakeFiles/cgutils.dir/src/mesh.cpp.o" \
"CMakeFiles/cgutils.dir/src/aabb.cpp.o" \
"CMakeFiles/cgutils.dir/src/ray.cpp.o" \
"CMakeFiles/cgutils.dir/src/texture.cpp.o" \
"CMakeFiles/cgutils.dir/src/light.cpp.o" \
"CMakeFiles/cgutils.dir/src/common.cpp.o" \
"CMakeFiles/cgutils.dir/src/entity.cpp.o" \
"CMakeFiles/cgutils.dir/src/material.cpp.o" \
"CMakeFiles/cgutils.dir/src/camera.cpp.o" \
"CMakeFiles/cgutils.dir/src/resources.cpp.o" \
"CMakeFiles/cgutils.dir/src/rtimage.cpp.o"

# External object files for target cgutils
cgutils_EXTERNAL_OBJECTS =

bin/libcgutils.a: CMakeFiles/cgutils.dir/src/mesh.cpp.o
bin/libcgutils.a: CMakeFiles/cgutils.dir/src/aabb.cpp.o
bin/libcgutils.a: CMakeFiles/cgutils.dir/src/ray.cpp.o
bin/libcgutils.a: CMakeFiles/cgutils.dir/src/texture.cpp.o
bin/libcgutils.a: CMakeFiles/cgutils.dir/src/light.cpp.o
bin/libcgutils.a: CMakeFiles/cgutils.dir/src/common.cpp.o
bin/libcgutils.a: CMakeFiles/cgutils.dir/src/entity.cpp.o
bin/libcgutils.a: CMakeFiles/cgutils.dir/src/material.cpp.o
bin/libcgutils.a: CMakeFiles/cgutils.dir/src/camera.cpp.o
bin/libcgutils.a: CMakeFiles/cgutils.dir/src/resources.cpp.o
bin/libcgutils.a: CMakeFiles/cgutils.dir/src/rtimage.cpp.o
bin/libcgutils.a: CMakeFiles/cgutils.dir/build.make
bin/libcgutils.a: CMakeFiles/cgutils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library bin/libcgutils.a"
	$(CMAKE_COMMAND) -P CMakeFiles/cgutils.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cgutils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cgutils.dir/build: bin/libcgutils.a
.PHONY : CMakeFiles/cgutils.dir/build

CMakeFiles/cgutils.dir/requires: CMakeFiles/cgutils.dir/src/mesh.cpp.o.requires
CMakeFiles/cgutils.dir/requires: CMakeFiles/cgutils.dir/src/aabb.cpp.o.requires
CMakeFiles/cgutils.dir/requires: CMakeFiles/cgutils.dir/src/ray.cpp.o.requires
CMakeFiles/cgutils.dir/requires: CMakeFiles/cgutils.dir/src/texture.cpp.o.requires
CMakeFiles/cgutils.dir/requires: CMakeFiles/cgutils.dir/src/light.cpp.o.requires
CMakeFiles/cgutils.dir/requires: CMakeFiles/cgutils.dir/src/common.cpp.o.requires
CMakeFiles/cgutils.dir/requires: CMakeFiles/cgutils.dir/src/entity.cpp.o.requires
CMakeFiles/cgutils.dir/requires: CMakeFiles/cgutils.dir/src/material.cpp.o.requires
CMakeFiles/cgutils.dir/requires: CMakeFiles/cgutils.dir/src/camera.cpp.o.requires
CMakeFiles/cgutils.dir/requires: CMakeFiles/cgutils.dir/src/resources.cpp.o.requires
CMakeFiles/cgutils.dir/requires: CMakeFiles/cgutils.dir/src/rtimage.cpp.o.requires
.PHONY : CMakeFiles/cgutils.dir/requires

CMakeFiles/cgutils.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cgutils.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cgutils.dir/clean

CMakeFiles/cgutils.dir/depend:
	cd /home/tim/workspace/cg-utils && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tim/workspace/cg-utils /home/tim/workspace/cg-utils /home/tim/workspace/cg-utils /home/tim/workspace/cg-utils /home/tim/workspace/cg-utils/CMakeFiles/cgutils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cgutils.dir/depend
