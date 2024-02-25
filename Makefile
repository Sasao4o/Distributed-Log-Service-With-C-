 
compileProtocolBuffer: 
	protoc --cpp_out=. api/v1/*.proto

compileDiskTest:
	g++ -o ./build/disk/File_test ./test/disk/File_test.cpp ./src/disk/File.cpp

compileIndexTest:
	 g++ -o ./build/index/index_test ./test/index/index_test.cpp ./src/index/index.cpp 

compileStoreTest:
	g++ -o ./build/store/store_test ./test/store/store_test.cpp ./src/store/store.cpp ./src/disk/File.cpp