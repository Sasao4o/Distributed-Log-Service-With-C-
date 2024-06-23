# tests/CMakeLists.txt

# Tests executables
add_executable(File_test
    "disk/File_test.cpp" "../src/disk/file.cpp")
add_executable(index_test
    "index/index_test.cpp" "../src/index/index.cpp" "../src/disk/file.cpp")
add_executable(store_test
    "store/store_test.cpp" "../src/store/store.cpp" "../src/disk/file.cpp")
add_executable(log_test
    "log/log_test.cpp" "../src/log/log.cpp" "../src/disk/file.cpp" "../src/segment/segment.cpp" "../src/index/index.cpp" "../src/store/store.cpp")
add_executable(segment_test
    "segment/segment_test.cpp" "../src/disk/file.cpp" "../src/segment/segment.cpp" "../src/index/index.cpp" "../src/store/store.cpp")
add_executable(grpc_test
    "grpc/grpc_test.cpp" "../src/log/log.cpp" "../src/disk/file.cpp" "../src/segment/segment.cpp" "../src/index/index.cpp" "../src/store/store.cpp" "../src/server/server.cpp" "../src/server/client.cpp")
target_compile_options(log_test PRIVATE -lprotobuf -pthread)
target_compile_options(segment_test PRIVATE -lprotobuf -pthread)
target_compile_options(grpc_test PRIVATE -lprotobuf -pthread)
target_link_libraries(segment_test
    logprog_grpc_proto
    )
target_link_libraries(log_test
    logprog_grpc_proto
    )

target_link_libraries(grpc_test
    logprog_grpc_proto
    )
