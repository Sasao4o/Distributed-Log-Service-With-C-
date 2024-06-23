cmake_minimum_required (VERSION 3.1)

project (SerfClientExample)

 include_directories( ${CMAKE_SOURCE_DIR}/include )
add_executable(agentFork agentFork.cpp)
add_executable( SerfClientExample SerfAgentExample.cpp )
add_executable( ClientExample SerfClientExample.cpp )
#SerfAgentExample
target_link_libraries(agentFork SerfCpp )
target_link_libraries(agentFork rt)
target_link_libraries( SerfClientExample SerfCpp )
target_link_libraries( SerfClientExample pthread )
target_link_libraries( ClientExample SerfCpp )
target_link_libraries( ClientExample pthread )