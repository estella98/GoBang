#include "RLGoBang.hpp"
#include "Decision.hpp"
#include <vector>
#include <string>
RLGoBang::RLGoBang(std::string location)
{
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, location, &db);
    this->db = db;
}
RLGoBang::~RLGoBang()
{
    delete this->db;
}
//
int RLGoBang::learn()
{
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
    }

    if (winner == P1)
    {
        this->writeData(P1Status, P1Decision);
    }
    else if (winner == P2)
    {
        this->writeData(P2Status, P2Decision);
    }
    return 0;
}

int RLGoBang::writeData(const std::vector<std::string> &status,
                        const std::vector<Point> &point)
{
    auto i = status.begin();
    auto j = point.begin();
    for (; i != status.end() && j != point.end(); ++i, ++j)
    {
        std::string temp;
        leveldb::Status s = db->Get(leveldb::ReadOptions(), *i, &temp);
        if (s.ok())
        {
            // Status exists;
            Decision decision(temp);
            decision.add1(*j);
            db->Put(leveldb::WriteOptions(), *i, decision.toStr());
        }
        else
        {
            // Status doesn't exists;
            Decision decision;
            decision.add1(*j);
            db->Put(leveldb::WriteOptions(), *i, decision.toStr());
        }
    }
    return 0;
}

//
int RLGoBang::learn(leveldb::DB *LearnedData)
{
    std::vector<std::string> P1Status, P2Status;
    std::vector<Point> P1Decision, P2Decision;

    Point tempPoint;
    Player tempPlayer;
    Player winner;
    GoBang game;
    int times = 0;
    while (true)
    {
        std::string sta(game.Status());
        std::string temp;
        leveldb::Status s;
        s = LearnedData->Get(leveldb::ReadOptions(), sta, &temp);
        if (s.ok())
        {
            Decision d(temp);
            game.PlayerPlay(P1, d.RandomChoice());
        }
        else
        {
            game.ComputerPlay(P1);
        }
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
        s = LearnedData->Get(leveldb::ReadOptions(), sta, &temp);
        if (s.ok())
        {
            Decision d(temp);
            game.PlayerPlay(P2, d.RandomChoice());
        }
        else
        {
            game.ComputerPlay(P2);
        }
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
    }

    if (winner == P1)
    {
        this->writeData(P1Status, P1Decision);
    }
    else if (winner == P2)
    {
        this->writeData(P2Status, P2Decision);
    }
    return 0;
}
//
int RLGoBang::ComputerPlayRandom(enum Player player)
{
    leveldb::Status s;
    std::string temp;
    s = db->Get(leveldb::ReadOptions(), chessBoard.toStr(), &temp);
    if (s.ok())
    {
        Decision d(temp);
        this->PlayerPlay(P1, d.RandomChoice());
    }
    else
    {
        this->ComputerPlay(P1);
    }
    return 0;
}
int RLGoBang::ComputerPlayBest(enum Player player)
{
    leveldb::Status s;
    std::string temp;
    s = db->Get(leveldb::ReadOptions(), chessBoard.toStr(), &temp);
    if (s.ok())
    {
        Decision d(temp);
        this->PlayerPlay(P1, d.BestChoice());
    }
    else
    {
        this->ComputerPlay(P1);
    }
    return 0;
}