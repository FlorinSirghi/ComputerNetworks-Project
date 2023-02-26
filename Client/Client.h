#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include "Includes.h"
#include "Card.h"
#include "Resources.h"
#include "Graphics.h"
#include "time.h"
#include "Room.h"

class Client
{
private:
    Graphics graphicsHandler;
    static Card deck[8];
    static Resources player, enemy;
    int turn;
    bool bothConnected;
    bool no_resources;
    bool playPressed;
    bool createRoomPressed;
    bool joinRoomPressed;
    bool gameOver;
    std::vector<Room>rooms;
    std::string joinedRoom;
    GLFWwindow* window;
    void pickAnotherCard(int deckPos);

    enum playerState{
        WELCOME_SCREEN,
        ROOMS_SCREEN,
        WAITING_ENEMY_SCREEN,
        JOINING_ROOM_SCREEN,
        IN_GAME
    };

    static playerState state;

    int serverDescriptor;
    sockaddr_in server;
    char name[100];
    char enemyName[100];
    char winner[100];
    bool submit;
    bool submitSecond;
    bool yourTurn;
    void sendRequest(std::string req);
    void getAnswer(std::string req);

    Client();
    void quit();
    void processInput(GLFWwindow* window);
    void handleDrawing();

    friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);



public:
    static Client& getInstance()
    {
        static Client *instance = new Client;
        return *instance;
    }

    void run();
    int init(char* serverAddress, char* port);
};

#endif
