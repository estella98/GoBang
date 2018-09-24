#include "GoBang.hpp"
#include "Player.hpp"
#include "Point.hpp"
#include <iostream>
#include "leveldb/db.h"
#include "Decision.hpp"
#include <vector>

void WriteToDatabase(int times,
                     const std::vector<std::string> &status,
                     const std::vector<Point> &point,
                     leveldb::DB *db);

int main()
{
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    std::vector<std::string> P1Status, P2Status;
    std::vector<Point> P1Decision, P2Decision;

    Point tempPoint;
    Player tempPlayer;
    Player winner;
    GoBang game;
    int times = 0;
    while (true)
    {
        game.ComputerPlay(P1);
        P1Status.push_back(game.Status());
        game.PreviousInfo(tempPoint, tempPlayer);
        P1Decision.push_back(tempPoint);
        game.PrintChessBoard();
        if (game.Victory())
        {
            winner = P1;
            std::cout << "P1" << std::endl;
            return 0;
        }
        game.ComputerPlay(P2);
        P2Status.push_back(game.Status());
        game.PreviousInfo(tempPoint, tempPlayer);
        P2Decision.push_back(tempPoint);
        game.PrintChessBoard();
        if (game.Victory())
        {
            winner = P2;
            std::cout << "P2" << std::endl;
            return 0;
        }
        ++times;
    }
    if (winner == P1)
    {
        WriteToDatabase(times, P1Status, P1Decision, db);
    }
    else if (winner == P2)
    {
        WriteToDatabase(times, P2Status, P2Decision, db);
    }
    return 0;
}

void WriteToDatabase(int times,
                     const std::vector<std::string> &status,
                     const std::vector<Point> &point,
                     leveldb::DB *db)
{
    for (int i = 0; i < times; ++i)
    {   
        std::string temp;
        leveldb::Status s = db->Get(leveldb::ReadOptions(), status[i], &temp);
        if (s.ok()){
            // Status exists;
            Decision decision(temp);
            decision.add1(point[i]);
            db->Put(leveldb::WriteOptions(), status[i], decision.toStr());
        }
        else{
            // Status doesn't exists;
            Decision decision;
            decision.add1(point[i]);
            db->Put(leveldb::WriteOptions(), status[i], decision.toStr());
        }
    }
}
