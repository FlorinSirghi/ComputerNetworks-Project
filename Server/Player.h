#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include "Includes.h"
#include "Resources.h"

class Player
{
public:
    enum playerState
    {
      IN_GAME,
      DISCONNECTED,
      GAME_OVER
    };
    playerState state;
    Resources resources;
    int playerDescriptor;
    std::string playerName;
    int playerID;
    int roomID;
    int orderInRoom;
    pthread_t thread;
    Player()
    {
        roomID = -1;
    };
    Player(int pd, int ID)
    {
        roomID = -1;
        playerDescriptor = pd;
        playerID = ID;
        state = IN_GAME;
    }
};

#endif