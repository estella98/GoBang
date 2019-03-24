# GoBang AI 
## Building

Execute
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DLEVELDB_DIRECTORY=<leveldb-base-dir>
cmake --build .
```
## Introduction
Gobang, also called Gomuku, or Five in a Row, is a traditional strategy board game. Two players take turn placing the stone on a 19 * 19 grid until one forms an unbroken chain of five stones horizontally, vertically, or diagonally and becomes the winner. This project implements the game in C++, which supplies multiple modes of player playing against each other and player playing against computer. 

## Reinforcement Learning Algorithm
To enhance the intelligence of computers in a battle, the program features with reinforcement learning mechanism to capture feedbacks under different circumstances on board and uses it to form long term strategy for the game. Enpowered by the fast key-value storage library LevelDB, each postion of the stone and corresponding state of the board could be swiftly recorded and retrieved as game goes. Decision made by the winning side will be emphasized in the calculation. A weighted random method is implemented to ensure the distribution of position maintains some levels of uncertainty.

## LevelDB
The program performes crud operations on LevelDB to access historical game data for AI module training. The database is light weight and well optimized in both performance and database size.


## Credits
LevelDB is a fast key-value storage library written at Google that provides an ordered mapping from string keys to string values.
View more at http://leveldb.org/
