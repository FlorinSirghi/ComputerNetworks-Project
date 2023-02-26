#ifndef SERVER_ROOM_H
#define SERVER_ROOM_H

#include "Includes.h"
#include "Resources.h"
#include "Player.h"

class Room
{
public:
    int playerNumber;
    int roomID;
    std::string name;
    Player player1, player2;
    bool modified;
    int turn;
    Room(std::string owner, int ID)
    {
        playerNumber = 1;
        name = owner + "'s room";
        modified = false;
        turn = 1;
        roomID = ID;
    }
    Room()
    {

    }
    Player& getEnemy(int id)
    {
        if(id == player1.playerID)
            return player2;
        return player1;
    }
    Player& getPlayer(int id)
    {
        if(id == player1.playerID)
            return player1;
        return player2;
    }
};

#endif
