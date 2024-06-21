# src/CMakeLists.txt

# Add source files to the CPP_LIST
set(CPP_LIST ${})
list(APPEND CPP_LIST 
"./log/log.cpp" 
"./disk/file.cpp" 
"./segment/segment.cpp" 
"./store/store.cpp" 
"./index/index.cpp" 
"./server/server.cpp" 
"./server/client.cpp")

include(${CMAKE_SOURCE_DIR}/comman.cmake)
# Proto file
get_filename_component(logprog_proto "${CMAKE_SOURCE_DIR}/api/v1/logprog.proto" ABSOLUTE)
get_filename_component(logprog_proto_path "${logprog_proto}" PATH)

# Generated sources
set(logprog_proto_srcs "${CMAKE_SOURCE_DIR}/cmake/build/logprog.pb.cc")
set(logprog_proto_hdrs "${CMAKE_SOURCE_DIR}/cmake/build/logprog.pb.h")
set(logprog_grpc_srcs "${CMAKE_SOURCE_DIR}/cmake/build/logprog.grpc.pb.cc")
set(logprog_grpc_hdrs "${CMAKE_SOURCE_DIR}/cmake/build/logprog.grpc.pb.h")
add_custom_command(
      OUTPUT "${logprog_proto_srcs}" "${logprog_proto_hdrs}" "${logprog_grpc_srcs}" "${logprog_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_SOURCE_DIR}/cmake/build"
        --cpp_out "${CMAKE_SOURCE_DIR}/cmake/build"
        -I "${logprog_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${logprog_proto}"
      DEPENDS "${logprog_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_SOURCE_DIR}/cmake/build")

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

# Targets route_guide_(client|server)
foreach(_target client server)
    file(GLOB RUNNER_FILE "${CMAKE_SOURCE_DIR}/src/server/${_target}_runner.cpp")

    add_executable(${_target} ${RUNNER_FILE} ${CPP_LIST})
    target_link_libraries(${_target}
        logprog_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF}
    )
endforeach()
