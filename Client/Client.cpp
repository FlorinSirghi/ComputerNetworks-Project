#include "Client.h"

Resources Client::player;
Resources Client::enemy;
Client::playerState Client::state;
Card Client::deck[8];

Client::Client()
{
    srand(time(0));

    for (int i = 0; i < 8; i++)
    {
        int r = rand() % 30;
        deck[i].setupCard(r);
    }

    float initialPos = 30;

    for (int i = 0; i < 8; i++)
        deck[i].setPos(initialPos + i * 120, 600);

    if ((serverDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("[CLIENT]Socket creation error. Error \n");
    }
    bothConnected = false;
    turn = 0;
    state = WELCOME_SCREEN;
    playPressed = false;
    submit = false;
    joinRoomPressed = false;
    createRoomPressed = false;
    submitSecond = false;
    gameOver = false;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && Client::state == Client::IN_GAME)
    {

        // check card
        std::string sel = "";
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int selection = -1;
        int i = 0;
        for (i = 0; i < 8; i++)
        {
            if (xpos >= Client::getInstance().deck[i].getX() && xpos <= Client::getInstance().deck[i].getX() + 120 &&
                ypos >= Client::getInstance().deck[i].getY() && ypos <= Client::getInstance().deck[i].getY() + 150)
            {
                sel = Client::getInstance().deck[i].getName();
                break;
            }
        }
        if (sel != "")
        {
            Client::getInstance().sendRequest("turn");
            if (Client::getInstance().turn == 1)
            {
                Client::getInstance().sendRequest(sel);
                if (Client::getInstance().no_resources == false)
                    Client::getInstance().pickAnotherCard(i);
            }
        }
    }
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseButtonEvent(button, action);
}

/*void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}*/

void Client::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        for (int i = 0; i < 8; i++)
        {
            if (xpos >= Client::getInstance().deck[i].getX() && xpos <= Client::getInstance().deck[i].getX() + 120 &&
                ypos >= Client::getInstance().deck[i].getY() && ypos <= Client::getInstance().deck[i].getY() + 100)
            {
                Client::getInstance().sendRequest("turn");
                if (Client::getInstance().turn == 1)
                {
                    Client::getInstance().sendRequest("disc");
                    Client::getInstance().pickAnotherCard(i);
                    break;
                }
            }
        }
    }
}

void Client::pickAnotherCard(int deckPos)
{
    int r = random() % 30;
    deck[deckPos].setupCard(r);
}

void Client::sendRequest(std::string req)
{
    if (write(serverDescriptor, req.c_str(), req.size()) < 0)
    {
        perror("[CLIENT]Error while sending the request ! \n");
    }
    else
        getAnswer(req);
}

void desirealize(Resources &p)
{
    p.builders = ntohl(p.builders);
    p.bricks = ntohl(p.bricks);
    p.soldiers = ntohl(p.soldiers);
    p.weapons = ntohl(p.weapons);
    p.magic = ntohl(p.magic);
    p.crystals = ntohl(p.crystals);
    p.fence = ntohl(p.fence);
    p.castle = ntohl(p.castle);
}

void printResources(Resources p)
{
    printf("Bricks: %d\n", p.bricks);
    fflush(stdout);
    printf("Builders: %d\n", p.builders);
    fflush(stdout);
    printf("Weapons: %d\n", p.weapons);
    fflush(stdout);
    printf("Soldiers: %d\n", p.soldiers);
    fflush(stdout);
    printf("Magic: %d\n", p.magic);
    fflush(stdout);
    printf("Crystals: %d\n", p.crystals);
    fflush(stdout);
    printf("Fence: %d\n", p.fence);
    fflush(stdout);
    printf("Castle: %d\n", p.castle);
    fflush(stdout);
}

void Client::getAnswer(std::string req)
{
    char answer[101];
    bzero(answer, 101);
    if (read(serverDescriptor, answer, 101) < 0)
    {
        perror("[CLIENT]Error while reading the answer ! \n");
    }
    else
    {
        if (req == "turn")
        {
            turn = atoi(answer);
        }
        /*if (req == "disc")
        {
            printf("%s\n", answer);
            fflush(stdout);
        }*/
        if (req == "create-room")
        {
            if (write(serverDescriptor, name, strlen(name)) < 0)
            {
                perror("[CLIENT]Error while sending the room name ! \n");
            }
        }
        if (req == "get-rooms")
        {
            char Nr[101];
            bzero(Nr, 101);
            char askForRoomsCount[101];
            strcpy(askForRoomsCount, "send-room-count");

            if (write(serverDescriptor, askForRoomsCount, strlen(askForRoomsCount)) < 0)
            {
                perror("[CLIENT]Error while sending the message ! \n");
            }
            else
            {
                if (read(serverDescriptor, &Nr, 101) < 0)
                {
                    perror("[CLIENT]Error while reading the answer ! \n");
                }
                else
                {
                    int roomsNr = atoi(Nr);
                    strcpy(askForRoomsCount, "send-room-name");

                    for (int i = 0; i < roomsNr; i++)
                    {
                        char roomName[101];
                        bzero(roomName, 101);
                        if (write(serverDescriptor, askForRoomsCount, strlen(askForRoomsCount)) < 0)
                        {
                            perror("[CLIENT]Error while sending the message ! \n");
                        }
                        else
                        {
                            if (read(serverDescriptor, roomName, 101) < 0)
                            {
                                perror("[CLIENT]Error while reading the answer ! \n");
                            }
                            else
                            {
                                Room a(roomName, 1);
                                rooms.push_back(a);
                            }
                        }
                    }
                }
            }
        }
        if (req == "has-enemy-joined")
        {
            if (strcmp(answer, "yes") == 0)
            {
                state = IN_GAME;
                createRoomPressed = false;
                bzero(enemyName, 100);
                if (read(serverDescriptor, enemyName, 100) < 0)
                {
                    perror("[CLIENT]Error while reading the answer ! \n");
                }
            }
        }
        if (req == "game-over")
        {
            if (strcmp(answer, "yes") == 0)
            {
                if (read(serverDescriptor, &winner, 100) < 0)
                {
                    perror("[CLIENT]Error while reading the answer ! \n");
                }
                else
                    gameOver = true;
            }
        }

        if (req.find("join-room") != std::string::npos)
        {
            if (write(serverDescriptor, name, strlen(name)) < 0)
            {
                perror("[CLIENT]Error while sending the message ! \n");
            }
            if (read(serverDescriptor, &enemyName, 100) < 0)
            {
                perror("[CLIENT]Error while reading the answer ! \n");
            }
        }

        if (req.find("card") != std::string::npos || req == "update")
        {
            if (req.find("card") != std::string::npos)
            {
                if (strcmp(answer, "no") == 0)
                    no_resources = true;
            }
            if (strcmp(answer, "no") != 0)
            {
                Resources player1Sv;
                if (read(serverDescriptor, &player1Sv, sizeof(Resources)) < 0)
                {
                    perror("[CLIENT]Error while reading the answer ! \n");
                }
                else
                {
                    desirealize(player1Sv);
                    player = player1Sv;
                }
                Resources player2Sv;
                if (read(serverDescriptor, &player2Sv, sizeof(Resources)) < 0)
                {
                    perror("[CLIENT]Error while reading the answer ! \n");
                }
                else
                {
                    desirealize(player2Sv);
                    enemy = player2Sv;
                }
            }
        }
    }
}

int Client::init(char *serverAddress, char *port)
{
    if (graphicsHandler.init() != 1)
    {
        printf("[CLIENT]Could not initialize graphics !\n");
        return -1;
    }
    glfwSetFramebufferSizeCallback(graphicsHandler.window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(graphicsHandler.window, mouse_button_callback);
    // glfwSetKeyCallback(graphicsHandler.window, key_callback);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(serverAddress);
    server.sin_port = htons(atoi(port));

    if (connect(serverDescriptor, (sockaddr *)&server, sizeof(sockaddr)) == -1)
    {
        perror("[CLIENT]Connection error. Error : \n");
        return errno;
    }

    return 1;
}

void Client::handleDrawing()
{
    if (createRoomPressed == true)
    {
        playPressed = false; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        state = WAITING_ENEMY_SCREEN;
        sendRequest("has-enemy-joined");
    }
    if (joinRoomPressed == true)
    {
        playPressed = false; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        state = JOINING_ROOM_SCREEN;
    }
    if (state == WELCOME_SCREEN)
        graphicsHandler.drawWelcome(playPressed);
    if (playPressed == true)
    {
        state = ROOMS_SCREEN;
        sendRequest("get-rooms");
    }

    if (state == ROOMS_SCREEN)
    {
        graphicsHandler.drawRooms(createRoomPressed, joinRoomPressed, joinedRoom, rooms);
        rooms.clear();
    }

    if (state == WAITING_ENEMY_SCREEN)
        graphicsHandler.drawWaitingEnemy(name, submit);

    if (state == JOINING_ROOM_SCREEN)
        graphicsHandler.drawJoiningRoom(name, submitSecond);

    if (submit == true)
    {
        sendRequest("create-room");
        submit = false;
    }
    if (submitSecond == true)
    {
        sendRequest("join-room-" + joinedRoom);
        state = IN_GAME;
        joinRoomPressed = false;
        submitSecond = false;
    }

    if (turn == 1)
        yourTurn = true;
    else
        yourTurn = false;

    if (state == IN_GAME)
        graphicsHandler.draw(player, enemy, deck, name, enemyName, yourTurn, gameOver, winner);
}

void Client::run()
{
    while (!glfwWindowShouldClose(graphicsHandler.window))
    {
        processInput(graphicsHandler.window);

        if (state == IN_GAME)
        {
            sendRequest("update");
            sendRequest("game-over");
        }

        no_resources = false;

        sendRequest("turn");

        handleDrawing();

        glfwPollEvents();
        glfwSwapBuffers(graphicsHandler.window);
    }

    quit();
}

void Client::quit()
{
    graphicsHandler.quit();
}
