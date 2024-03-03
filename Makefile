 
compileProtocolBuffer: 
	protoc --cpp_out=. api/v1/*.proto
 
compileProject:
	g++ -std=c++17 -o ./exc ./main.cpp ./api/v1/log.pb.cc ./src/disk/File.cpp ./src/log/log.cpp ./src/segment/segment.cpp ./src/index/index.cpp ./src/store/store.cpp -lprotobuf -pthread

compileDiskTest:
	g++ -o ./build/disk/File_test ./test/disk/File_test.cpp ./src/disk/File.cpp

compileIndexTest:
	 g++ -o ./build/index/index_test ./test/index/index_test.cpp ./src/index/index.cpp ./src/disk/File.cpp

compileStoreTest:
	g++ -o ./build/store/store_test ./test/store/store_test.cpp ./src/store/store.cpp ./src/disk/File.cpp

compileSegmentTest:
	g++ -o ./build/segment/segment_test ./test/segment/segment_test.cpp ./cmake/build/log.pb.cc ./src/disk/File.cpp ./src/segment/segment.cpp ./src/index/index.cpp ./src/store/store.cpp -lprotobuf -pthread

runSegmentTest: 
	g++ -o ./build/segment/segment_test ./test/segment/segment_test.cpp ./api/v1/logprog.pb.cc ./src/disk/File.cpp ./src/segment/segment.cpp ./src/index/index.cpp ./src/store/store.cpp -lprotobuf -pthread && ./build/segment/segment_test

runStoreTest:
	g++ -o ./build/store/store_test ./test/store/store_test.cpp ./src/store/store.cpp ./src/disk/File.cpp && ./build/store/store_test

runLogTest:
	g++ -std=c++17 -o ./build/log/log_test ./test/log/log_test.cpp ./src/log/log.cpp ./src/segment/segment.cpp ./src/store/store.cpp ./src/index/index.cpp ./cmake/build/logprog.pb.cc ./src/disk/File.cpp -lprotobuf -pthread && ./build/log/log_test
