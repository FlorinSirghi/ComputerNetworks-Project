#ifndef CLIENT_ROOM_H
#define CLIENT_ROOM_H

#include "Includes.h"

class Room
{
public:
    std::string name;
    int playerNumber;
    bool joined;
    Room(std::string n, int pn)
    {
        joined = false;
        name = n;
        playerNumber = pn;
    }
};

#endif