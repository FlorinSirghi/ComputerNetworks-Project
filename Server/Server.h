#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "Includes.h"
#include "Card.h"
#include "Room.h"
#include "Player.h"
#include "Bot.h"

class Server
{
private:

    int PORT;
    sockaddr_in server;
    sockaddr_in client1;
    int serverDescriptor;

    Server();
    void getRequest(Player, int index);
    friend void *player(void *args);

    friend void printResources(Resources p);

    int init();
    std::string gameOver(Player p1, Player p2);

public:

    static std::vector<Room> rooms;
    static std::vector<Player> players;
    static int ID;
    static int roomIDS;
    //pattern-ul singleton, care permite o singura instanta a clasei Server
    static Server& getInstance()
    {
        static Server *instance = new Server;
        return *instance;
    }

    void run();
};


#endif
