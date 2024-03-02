# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# cmake build file for C++ route_guide example.
# Assumes protobuf and gRPC have been installed using cmake.
# See cmake_externalproject/CMakeLists.txt for all-in-one cmake build
# that automatically builds all the dependencies before building route_guide.

cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PROLOG C CXX)

 include(./comman.cmake)

# Proto file
get_filename_component(logprog_proto "./api/v1/logprog.proto" ABSOLUTE)
get_filename_component(logprog_proto_path "${logprog_proto}" PATH)

# Generated sources
set(logprog_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/logprog.pb.cc")
set(logprog_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/logprog.pb.h")
set(logprog_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/logprog.grpc.pb.cc")
set(logprog_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/logprog.grpc.pb.h")
add_custom_command(
      OUTPUT "${logprog_proto_srcs}" "${logprog_proto_hdrs}" "${logprog_grpc_srcs}" "${logprog_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${logprog_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${logprog_proto}"
      DEPENDS "${logprog_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# rg_grpc_proto
add_library(logprog_grpc_proto
  ${logprog_grpc_srcs}
  ${logprog_grpc_hdrs}
  ${logprog_proto_srcs}
  ${logprog_proto_hdrs})
target_link_libraries(logprog_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# # route_guide_helper
 
# target_link_libraries(route_guide_helper
#   rg_grpc_proto
#   ${_REFLECTION}
#   ${_GRPC_GRPCPP}
#   ${_PROTOBUF_LIBPROTOBUF})

# Targets route_guide_(client|server)
foreach(_target
  client server)
  add_executable(${_target}
    "./src/server/${_target}.cpp" "./src/log/log.cpp" "./src/disk/file.cpp" "./src/segment/segment.cpp" "./src/store/store.cpp" "./src/index/index.cpp")
  target_link_libraries(${_target}
    logprog_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    )
endforeach()