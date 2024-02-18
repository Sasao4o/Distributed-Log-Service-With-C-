 
compileProtocolBuffer: 
	protoc --cpp_out=. api/v1/*.proto

compileCpp: 
	g++ -o ./o ./main.cpp ./src/disk/File.cpp