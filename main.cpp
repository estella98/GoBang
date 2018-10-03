#include "RLGoBang.hpp"
#include "Player.hpp"
#include "leveldb/db.h"
#include <iostream>

int main()
{
    RLGoBang game1("/tmp/data2");
    // create a empty database
    for (int i = 0; i < 100; i++)
    {
        // learn data without trained data
        game1.learn();
    }

    // leveldb::DB *db;
    // leveldb::Options options;
    // options.create_if_missing = false;
    // leveldb::Status status = leveldb::DB::Open(options, "/tmp/data1", &db);
    // // load trained data
    // RLGoBang game2("/tmp/data2");
    // // create a empty database
    // for (int i = 0; i < 100000000; i++)
    // {
    //     // learn data based on trained data
    //     game1.learn(db); // bug
    // }

    // RLGoBang game3("/tmp/data1");
    // // open a existed database
    // for (int i = 0; i < 100; i++)
    // {
    //     // learn data without trained data
    //     game1.learn();
    // }

    // use trained data to play with palyer
    Player winner;
    while (true)
    {
        game1.ComputerPlayBest(P1);
        game1.PrintChessBoard();
        if (game1.Victory())
        {
            winner = P1;
            std::cout << "P1" << std::endl;
            return 0;
        }
        Point pt;

        std::cin >> pt.x >> pt.y;
        game1.PlayerPlay(P2, pt);
        game1.PrintChessBoard();
        if (game1.Victory())
        {
            winner = P2;
            std::cout << "P2" << std::endl;
            return 0;
        }
    }
    return 0;
}
