#ifndef CLIENT_GRAPHICS_H
#define CLIENT_GRAPHICS_H

#include "Includes.h"
#include "Resources.h"
#include "Card.h"
#include "Room.h"

class Graphics
{
public:
    GLFWwindow* window;
    Graphics();
    int init();
    void draw(Resources player, Resources enemy, Card deck[8], char* playerName, char* enemyName, bool yourTurn, bool gameOver, char* winner);
    void drawWelcome(bool& playPressed);
    void drawRooms(bool& createRoomPressed, bool& joinRoomPressed, std::string &joinedRoom, std::vector<Room> rooms);
    void drawWaitingEnemy(char* name, bool& submit);
    void drawJoiningRoom(char* name, bool& submit);
    void drawCastlesWalls();
    void quit();
    bool submited;
    bool submitedSecond;
    int dotNumber = 0;
};


#endif
