# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build"

# Include any dependencies generated for this target.
include CMakeFiles/log_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/log_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/log_test.dir/flags.make

logprog.pb.cc: ../../api/v1/logprog.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Generating logprog.pb.cc, logprog.pb.h, logprog.grpc.pb.cc, logprog.grpc.pb.h"
	/home/sasa/.local/bin/protoc-25.1.0 --grpc_out /mnt/c/Users/pc/Desktop/wael\ ds/as3/Distributed-Log-Service-With-C-/cmake/build --cpp_out /mnt/c/Users/pc/Desktop/wael\ ds/as3/Distributed-Log-Service-With-C-/cmake/build -I /mnt/c/Users/pc/Desktop/wael\ ds/as3/Distributed-Log-Service-With-C-/api/v1 --plugin=protoc-gen-grpc="/home/sasa/.local/bin/grpc_cpp_plugin" /mnt/c/Users/pc/Desktop/wael\ ds/as3/Distributed-Log-Service-With-C-/api/v1/logprog.proto

logprog.pb.h: logprog.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate logprog.pb.h

logprog.grpc.pb.cc: logprog.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate logprog.grpc.pb.cc

logprog.grpc.pb.h: logprog.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate logprog.grpc.pb.h

CMakeFiles/log_test.dir/test/log/log_test.cpp.o: CMakeFiles/log_test.dir/flags.make
CMakeFiles/log_test.dir/test/log/log_test.cpp.o: ../../test/log/log_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/log_test.dir/test/log/log_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/log_test.dir/test/log/log_test.cpp.o -c "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/test/log/log_test.cpp"

CMakeFiles/log_test.dir/test/log/log_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/log_test.dir/test/log/log_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/test/log/log_test.cpp" > CMakeFiles/log_test.dir/test/log/log_test.cpp.i

CMakeFiles/log_test.dir/test/log/log_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/log_test.dir/test/log/log_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/test/log/log_test.cpp" -o CMakeFiles/log_test.dir/test/log/log_test.cpp.s

CMakeFiles/log_test.dir/src/log/log.cpp.o: CMakeFiles/log_test.dir/flags.make
CMakeFiles/log_test.dir/src/log/log.cpp.o: ../../src/log/log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/log_test.dir/src/log/log.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/log_test.dir/src/log/log.cpp.o -c "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/log/log.cpp"

CMakeFiles/log_test.dir/src/log/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/log_test.dir/src/log/log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/log/log.cpp" > CMakeFiles/log_test.dir/src/log/log.cpp.i

CMakeFiles/log_test.dir/src/log/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/log_test.dir/src/log/log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/log/log.cpp" -o CMakeFiles/log_test.dir/src/log/log.cpp.s

CMakeFiles/log_test.dir/logprog.pb.cc.o: CMakeFiles/log_test.dir/flags.make
CMakeFiles/log_test.dir/logprog.pb.cc.o: logprog.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/log_test.dir/logprog.pb.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/log_test.dir/logprog.pb.cc.o -c "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build/logprog.pb.cc"

CMakeFiles/log_test.dir/logprog.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/log_test.dir/logprog.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build/logprog.pb.cc" > CMakeFiles/log_test.dir/logprog.pb.cc.i

CMakeFiles/log_test.dir/logprog.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/log_test.dir/logprog.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build/logprog.pb.cc" -o CMakeFiles/log_test.dir/logprog.pb.cc.s

CMakeFiles/log_test.dir/src/disk/File.cpp.o: CMakeFiles/log_test.dir/flags.make
CMakeFiles/log_test.dir/src/disk/File.cpp.o: ../../src/disk/File.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/log_test.dir/src/disk/File.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/log_test.dir/src/disk/File.cpp.o -c "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/disk/File.cpp"

CMakeFiles/log_test.dir/src/disk/File.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/log_test.dir/src/disk/File.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/disk/File.cpp" > CMakeFiles/log_test.dir/src/disk/File.cpp.i

CMakeFiles/log_test.dir/src/disk/File.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/log_test.dir/src/disk/File.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/disk/File.cpp" -o CMakeFiles/log_test.dir/src/disk/File.cpp.s

CMakeFiles/log_test.dir/src/segment/segment.cpp.o: CMakeFiles/log_test.dir/flags.make
CMakeFiles/log_test.dir/src/segment/segment.cpp.o: ../../src/segment/segment.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/log_test.dir/src/segment/segment.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/log_test.dir/src/segment/segment.cpp.o -c "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/segment/segment.cpp"

CMakeFiles/log_test.dir/src/segment/segment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/log_test.dir/src/segment/segment.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/segment/segment.cpp" > CMakeFiles/log_test.dir/src/segment/segment.cpp.i

CMakeFiles/log_test.dir/src/segment/segment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/log_test.dir/src/segment/segment.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/segment/segment.cpp" -o CMakeFiles/log_test.dir/src/segment/segment.cpp.s

CMakeFiles/log_test.dir/src/index/index.cpp.o: CMakeFiles/log_test.dir/flags.make
CMakeFiles/log_test.dir/src/index/index.cpp.o: ../../src/index/index.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/log_test.dir/src/index/index.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/log_test.dir/src/index/index.cpp.o -c "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/index/index.cpp"

CMakeFiles/log_test.dir/src/index/index.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/log_test.dir/src/index/index.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/index/index.cpp" > CMakeFiles/log_test.dir/src/index/index.cpp.i

CMakeFiles/log_test.dir/src/index/index.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/log_test.dir/src/index/index.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/index/index.cpp" -o CMakeFiles/log_test.dir/src/index/index.cpp.s

CMakeFiles/log_test.dir/src/store/store.cpp.o: CMakeFiles/log_test.dir/flags.make
CMakeFiles/log_test.dir/src/store/store.cpp.o: ../../src/store/store.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/log_test.dir/src/store/store.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/log_test.dir/src/store/store.cpp.o -c "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/store/store.cpp"

CMakeFiles/log_test.dir/src/store/store.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/log_test.dir/src/store/store.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/store/store.cpp" > CMakeFiles/log_test.dir/src/store/store.cpp.i

CMakeFiles/log_test.dir/src/store/store.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/log_test.dir/src/store/store.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/src/store/store.cpp" -o CMakeFiles/log_test.dir/src/store/store.cpp.s

# Object files for target log_test
log_test_OBJECTS = \
"CMakeFiles/log_test.dir/test/log/log_test.cpp.o" \
"CMakeFiles/log_test.dir/src/log/log.cpp.o" \
"CMakeFiles/log_test.dir/logprog.pb.cc.o" \
"CMakeFiles/log_test.dir/src/disk/File.cpp.o" \
"CMakeFiles/log_test.dir/src/segment/segment.cpp.o" \
"CMakeFiles/log_test.dir/src/index/index.cpp.o" \
"CMakeFiles/log_test.dir/src/store/store.cpp.o"

# External object files for target log_test
log_test_EXTERNAL_OBJECTS =

log_test: CMakeFiles/log_test.dir/test/log/log_test.cpp.o
log_test: CMakeFiles/log_test.dir/src/log/log.cpp.o
log_test: CMakeFiles/log_test.dir/logprog.pb.cc.o
log_test: CMakeFiles/log_test.dir/src/disk/File.cpp.o
log_test: CMakeFiles/log_test.dir/src/segment/segment.cpp.o
log_test: CMakeFiles/log_test.dir/src/index/index.cpp.o
log_test: CMakeFiles/log_test.dir/src/store/store.cpp.o
log_test: CMakeFiles/log_test.dir/build.make
log_test: liblogprog_grpc_proto.a
log_test: /home/sasa/.local/lib/libgrpc++_reflection.a
log_test: /home/sasa/.local/lib/libgrpc++.a
log_test: /home/sasa/.local/lib/libprotobuf.a
log_test: /home/sasa/.local/lib/libgrpc.a
log_test: /home/sasa/.local/lib/libupb_json_lib.a
log_test: /home/sasa/.local/lib/libupb_textformat_lib.a
log_test: /home/sasa/.local/lib/libupb_message_lib.a
log_test: /home/sasa/.local/lib/libupb_base_lib.a
log_test: /home/sasa/.local/lib/libupb_mem_lib.a
log_test: /home/sasa/.local/lib/libutf8_range_lib.a
log_test: /home/sasa/.local/lib/libre2.a
log_test: /home/sasa/.local/lib/libz.a
log_test: /home/sasa/.local/lib/libcares.a
log_test: /home/sasa/.local/lib/libgpr.a
log_test: /home/sasa/.local/lib/libabsl_random_distributions.a
log_test: /home/sasa/.local/lib/libabsl_random_seed_sequences.a
log_test: /home/sasa/.local/lib/libabsl_random_internal_pool_urbg.a
log_test: /home/sasa/.local/lib/libabsl_random_internal_randen.a
log_test: /home/sasa/.local/lib/libabsl_random_internal_randen_hwaes.a
log_test: /home/sasa/.local/lib/libabsl_random_internal_randen_hwaes_impl.a
log_test: /home/sasa/.local/lib/libabsl_random_internal_randen_slow.a
log_test: /home/sasa/.local/lib/libabsl_random_internal_platform.a
log_test: /home/sasa/.local/lib/libabsl_random_internal_seed_material.a
log_test: /home/sasa/.local/lib/libabsl_random_seed_gen_exception.a
log_test: /home/sasa/.local/lib/libssl.a
log_test: /home/sasa/.local/lib/libcrypto.a
log_test: /home/sasa/.local/lib/libaddress_sorting.a
log_test: /home/sasa/.local/lib/libabsl_log_internal_check_op.a
log_test: /home/sasa/.local/lib/libabsl_leak_check.a
log_test: /home/sasa/.local/lib/libabsl_die_if_null.a
log_test: /home/sasa/.local/lib/libabsl_log_internal_conditions.a
log_test: /home/sasa/.local/lib/libabsl_log_internal_message.a
log_test: /home/sasa/.local/lib/libabsl_log_internal_nullguard.a
log_test: /home/sasa/.local/lib/libabsl_examine_stack.a
log_test: /home/sasa/.local/lib/libabsl_log_internal_format.a
log_test: /home/sasa/.local/lib/libabsl_log_internal_proto.a
log_test: /home/sasa/.local/lib/libabsl_log_internal_log_sink_set.a
log_test: /home/sasa/.local/lib/libabsl_log_sink.a
log_test: /home/sasa/.local/lib/libabsl_log_entry.a
log_test: /home/sasa/.local/lib/libabsl_flags_internal.a
log_test: /home/sasa/.local/lib/libabsl_flags_marshalling.a
log_test: /home/sasa/.local/lib/libabsl_flags_reflection.a
log_test: /home/sasa/.local/lib/libabsl_flags_config.a
log_test: /home/sasa/.local/lib/libabsl_flags_program_name.a
log_test: /home/sasa/.local/lib/libabsl_flags_private_handle_accessor.a
log_test: /home/sasa/.local/lib/libabsl_flags_commandlineflag.a
log_test: /home/sasa/.local/lib/libabsl_flags_commandlineflag_internal.a
log_test: /home/sasa/.local/lib/libabsl_log_initialize.a
log_test: /home/sasa/.local/lib/libabsl_log_globals.a
log_test: /home/sasa/.local/lib/libabsl_vlog_config_internal.a
log_test: /home/sasa/.local/lib/libabsl_log_internal_fnmatch.a
log_test: /home/sasa/.local/lib/libabsl_log_internal_globals.a
log_test: /home/sasa/.local/lib/libabsl_raw_hash_set.a
log_test: /home/sasa/.local/lib/libabsl_hash.a
log_test: /home/sasa/.local/lib/libabsl_city.a
log_test: /home/sasa/.local/lib/libabsl_low_level_hash.a
log_test: /home/sasa/.local/lib/libabsl_hashtablez_sampler.a
log_test: /home/sasa/.local/lib/libabsl_statusor.a
log_test: /home/sasa/.local/lib/libabsl_status.a
log_test: /home/sasa/.local/lib/libabsl_cord.a
log_test: /home/sasa/.local/lib/libabsl_cordz_info.a
log_test: /home/sasa/.local/lib/libabsl_cord_internal.a
log_test: /home/sasa/.local/lib/libabsl_cordz_functions.a
log_test: /home/sasa/.local/lib/libabsl_exponential_biased.a
log_test: /home/sasa/.local/lib/libabsl_cordz_handle.a
log_test: /home/sasa/.local/lib/libabsl_crc_cord_state.a
log_test: /home/sasa/.local/lib/libabsl_crc32c.a
log_test: /home/sasa/.local/lib/libabsl_crc_internal.a
log_test: /home/sasa/.local/lib/libabsl_crc_cpu_detect.a
log_test: /home/sasa/.local/lib/libabsl_bad_optional_access.a
log_test: /home/sasa/.local/lib/libabsl_strerror.a
log_test: /home/sasa/.local/lib/libabsl_str_format_internal.a
log_test: /home/sasa/.local/lib/libabsl_synchronization.a
log_test: /home/sasa/.local/lib/libabsl_stacktrace.a
log_test: /home/sasa/.local/lib/libabsl_symbolize.a
log_test: /home/sasa/.local/lib/libabsl_debugging_internal.a
log_test: /home/sasa/.local/lib/libabsl_demangle_internal.a
log_test: /home/sasa/.local/lib/libabsl_graphcycles_internal.a
log_test: /home/sasa/.local/lib/libabsl_kernel_timeout_internal.a
log_test: /home/sasa/.local/lib/libabsl_malloc_internal.a
log_test: /home/sasa/.local/lib/libabsl_time.a
log_test: /home/sasa/.local/lib/libabsl_civil_time.a
log_test: /home/sasa/.local/lib/libabsl_time_zone.a
log_test: /home/sasa/.local/lib/libabsl_bad_variant_access.a
log_test: /home/sasa/.local/lib/libutf8_validity.a
log_test: /home/sasa/.local/lib/libabsl_strings.a
log_test: /home/sasa/.local/lib/libabsl_int128.a
log_test: /home/sasa/.local/lib/libabsl_strings_internal.a
log_test: /home/sasa/.local/lib/libabsl_string_view.a
log_test: /home/sasa/.local/lib/libabsl_base.a
log_test: /home/sasa/.local/lib/libabsl_spinlock_wait.a
log_test: /home/sasa/.local/lib/libabsl_throw_delegate.a
log_test: /home/sasa/.local/lib/libabsl_raw_logging_internal.a
log_test: /home/sasa/.local/lib/libabsl_log_severity.a
log_test: CMakeFiles/log_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable log_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/log_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/log_test.dir/build: log_test

.PHONY : CMakeFiles/log_test.dir/build

CMakeFiles/log_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/log_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/log_test.dir/clean

CMakeFiles/log_test.dir/depend: logprog.pb.cc
CMakeFiles/log_test.dir/depend: logprog.pb.h
CMakeFiles/log_test.dir/depend: logprog.grpc.pb.cc
CMakeFiles/log_test.dir/depend: logprog.grpc.pb.h
	cd "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-" "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-" "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build" "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build" "/mnt/c/Users/pc/Desktop/wael ds/as3/Distributed-Log-Service-With-C-/cmake/build/CMakeFiles/log_test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/log_test.dir/depend
