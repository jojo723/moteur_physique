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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/florent/workspace/MoteurPhysique

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/florent/workspace/MoteurPhysique/build

# Include any dependencies generated for this target.
include CMakeFiles/Flag.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Flag.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Flag.dir/flags.make

CMakeFiles/Flag.dir/src/main.cpp.o: CMakeFiles/Flag.dir/flags.make
CMakeFiles/Flag.dir/src/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/florent/workspace/MoteurPhysique/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Flag.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Flag.dir/src/main.cpp.o -c /home/florent/workspace/MoteurPhysique/src/main.cpp

CMakeFiles/Flag.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Flag.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/florent/workspace/MoteurPhysique/src/main.cpp > CMakeFiles/Flag.dir/src/main.cpp.i

CMakeFiles/Flag.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Flag.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/florent/workspace/MoteurPhysique/src/main.cpp -o CMakeFiles/Flag.dir/src/main.cpp.s

CMakeFiles/Flag.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/Flag.dir/src/main.cpp.o.requires

CMakeFiles/Flag.dir/src/main.cpp.o.provides: CMakeFiles/Flag.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Flag.dir/build.make CMakeFiles/Flag.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/Flag.dir/src/main.cpp.o.provides

CMakeFiles/Flag.dir/src/main.cpp.o.provides.build: CMakeFiles/Flag.dir/src/main.cpp.o

CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o: CMakeFiles/Flag.dir/flags.make
CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o: ../src/renderer/ParticleRenderer2D.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/florent/workspace/MoteurPhysique/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o -c /home/florent/workspace/MoteurPhysique/src/renderer/ParticleRenderer2D.cpp

CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/florent/workspace/MoteurPhysique/src/renderer/ParticleRenderer2D.cpp > CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.i

CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/florent/workspace/MoteurPhysique/src/renderer/ParticleRenderer2D.cpp -o CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.s

CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o.requires:
.PHONY : CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o.requires

CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o.provides: CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o.requires
	$(MAKE) -f CMakeFiles/Flag.dir/build.make CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o.provides.build
.PHONY : CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o.provides

CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o.provides.build: CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o

CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o: CMakeFiles/Flag.dir/flags.make
CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o: ../src/renderer/BallRenderer3D.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/florent/workspace/MoteurPhysique/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o -c /home/florent/workspace/MoteurPhysique/src/renderer/BallRenderer3D.cpp

CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/florent/workspace/MoteurPhysique/src/renderer/BallRenderer3D.cpp > CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.i

CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/florent/workspace/MoteurPhysique/src/renderer/BallRenderer3D.cpp -o CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.s

CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o.requires:
.PHONY : CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o.requires

CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o.provides: CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o.requires
	$(MAKE) -f CMakeFiles/Flag.dir/build.make CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o.provides.build
.PHONY : CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o.provides

CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o.provides.build: CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o

CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o: CMakeFiles/Flag.dir/flags.make
CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o: ../src/renderer/WindowManager.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/florent/workspace/MoteurPhysique/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o -c /home/florent/workspace/MoteurPhysique/src/renderer/WindowManager.cpp

CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/florent/workspace/MoteurPhysique/src/renderer/WindowManager.cpp > CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.i

CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/florent/workspace/MoteurPhysique/src/renderer/WindowManager.cpp -o CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.s

CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o.requires:
.PHONY : CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o.requires

CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o.provides: CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o.requires
	$(MAKE) -f CMakeFiles/Flag.dir/build.make CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o.provides.build
.PHONY : CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o.provides

CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o.provides.build: CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o

CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o: CMakeFiles/Flag.dir/flags.make
CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o: ../src/renderer/GLtools.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/florent/workspace/MoteurPhysique/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o -c /home/florent/workspace/MoteurPhysique/src/renderer/GLtools.cpp

CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/florent/workspace/MoteurPhysique/src/renderer/GLtools.cpp > CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.i

CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/florent/workspace/MoteurPhysique/src/renderer/GLtools.cpp -o CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.s

CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o.requires:
.PHONY : CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o.requires

CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o.provides: CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o.requires
	$(MAKE) -f CMakeFiles/Flag.dir/build.make CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o.provides.build
.PHONY : CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o.provides

CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o.provides.build: CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o

# Object files for target Flag
Flag_OBJECTS = \
"CMakeFiles/Flag.dir/src/main.cpp.o" \
"CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o" \
"CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o" \
"CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o" \
"CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o"

# External object files for target Flag
Flag_EXTERNAL_OBJECTS =

Flag: CMakeFiles/Flag.dir/src/main.cpp.o
Flag: CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o
Flag: CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o
Flag: CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o
Flag: CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o
Flag: third-party/glew-1.10.0/libglew.a
Flag: /usr/lib/x86_64-linux-gnu/libGLU.so
Flag: /usr/lib/x86_64-linux-gnu/libGL.so
Flag: /usr/lib/x86_64-linux-gnu/libSM.so
Flag: /usr/lib/x86_64-linux-gnu/libICE.so
Flag: /usr/lib/x86_64-linux-gnu/libX11.so
Flag: /usr/lib/x86_64-linux-gnu/libXext.so
Flag: /usr/lib/x86_64-linux-gnu/libSDLmain.a
Flag: /usr/lib/x86_64-linux-gnu/libSDL.so
Flag: CMakeFiles/Flag.dir/build.make
Flag: CMakeFiles/Flag.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Flag"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Flag.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Flag.dir/build: Flag
.PHONY : CMakeFiles/Flag.dir/build

CMakeFiles/Flag.dir/requires: CMakeFiles/Flag.dir/src/main.cpp.o.requires
CMakeFiles/Flag.dir/requires: CMakeFiles/Flag.dir/src/renderer/ParticleRenderer2D.cpp.o.requires
CMakeFiles/Flag.dir/requires: CMakeFiles/Flag.dir/src/renderer/BallRenderer3D.cpp.o.requires
CMakeFiles/Flag.dir/requires: CMakeFiles/Flag.dir/src/renderer/WindowManager.cpp.o.requires
CMakeFiles/Flag.dir/requires: CMakeFiles/Flag.dir/src/renderer/GLtools.cpp.o.requires
.PHONY : CMakeFiles/Flag.dir/requires

CMakeFiles/Flag.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Flag.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Flag.dir/clean

CMakeFiles/Flag.dir/depend:
	cd /home/florent/workspace/MoteurPhysique/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/florent/workspace/MoteurPhysique /home/florent/workspace/MoteurPhysique /home/florent/workspace/MoteurPhysique/build /home/florent/workspace/MoteurPhysique/build /home/florent/workspace/MoteurPhysique/build/CMakeFiles/Flag.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Flag.dir/depend

