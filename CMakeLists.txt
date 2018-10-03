cmake_minimum_required(VERSION 3.9)

option(LEVELDB_DIRECTORY "Base directory to leveldb" /usr/local/Cellar/leveldb/1.20_2)

set(CMAKE_CXX_STANDARD 17)

include_directories("${LEVELDB_DIRECTORY}/include")
link_directories("${LEVELDB_DIRECTORY}/lib")
add_executable(GoBang
	Chessboard.cpp
	GoBang.cpp
	main.cpp
	Decision.cpp
	RLGoBang.cpp
)
target_link_libraries(GoBang leveldb)
