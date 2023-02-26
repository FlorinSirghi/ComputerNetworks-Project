#include "Server.h"

Server::Server()
{
    PORT = 1500;
}

std::vector<Room> Server::rooms;
std::vector<Player> Server::players;
int Server::ID = 0;
int Server::roomIDS = 200;

std::string Server::gameOver(Player p1, Player p2)
{
    if (p1.resources.castle <= 0 || p2.resources.castle >= 100)
        return p2.playerName;
    if (p1.resources.castle >= 100 || p2.resources.castle <= 0)
        return p1.playerName;

    return "no";
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

void serialize(Resources &p)
{
    p.builders = htonl(p.builders);
    p.bricks = htonl(p.bricks);
    p.soldiers = htonl(p.soldiers);
    p.weapons = htonl(p.weapons);
    p.magic = htonl(p.magic);
    p.crystals = htonl(p.crystals);
    p.castle = htonl(p.castle);
    p.fence = htonl(p.fence);
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

void Server::getRequest(Player p, int playerIndex)
{
    int index = -1;
    for (int i = 0; i < Server::rooms.size(); i++)
        if (p.playerID == rooms[i].player1.playerID || p.playerID == rooms[i].player2.playerID)
        {
            index = i;
            break;
        }
    char request[101];
    bzero(request, 101);
    int bytesRead = -1;
    if ((bytesRead = read(p.playerDescriptor, request, 101)) < 0)
    {
        perror("[SERVER]Error while reading the request ! Error \n");
    }
    else
    {
        if (bytesRead == 0)
        {
            players[playerIndex].state = Player::DISCONNECTED;
            printf("Player : %s disconnected\n", rooms[index].getPlayer(p.playerID).playerName.c_str());
            fflush(stdout);
            return;
        }
        std::string req = request;
        std::string ans;
        if (req == "turn")
        {
            if (index != -1 && (p.playerID % 2) == rooms[index].turn)
                ans = "1";
            else
                ans = "0";
        }
        if (req == "disc")
        {
            if (index != -1)
            {
                if (rooms[index].turn == 1)
                    rooms[index].turn = 0;
                else
                    rooms[index].turn = 1;
            }
            ans = "discarded";
        }
        if (req == "update")
        {
            if (index != -1 && rooms[index].modified == true)
            {
                ans = "done";
                rooms[index].modified = false;
            }
            else
                ans = "no";
        }
        if (req == "create-room")
        {
            ans = "Creating room...";
        }
        if (req == "get-rooms")
        {
            ans = "Returning rooms...";
        }
        if (req == "has-enemy-joined")
        {
            if (index != -1 && rooms[index].playerNumber == 2)
            {
                ans = "yes";
            }
            else
            {
                ans = "no";
            }
        }
        if (req.find("join-room") != std::string::npos)
        {
            std::string roomName = (req.c_str()) + 10;
            for (int i = 0; i < rooms.size(); i++)
                if (roomName == rooms[i].name)
                {
                    rooms[i].playerNumber = 2;
                    rooms[i].player2 = p;
                    rooms[i].player2.orderInRoom = 2;
                }
            ans = "Joined room";
        }

        if (req == "game-over")
        {
            std::string winner = gameOver(rooms[index].getPlayer(p.playerID), rooms[index].getEnemy(p.playerID));
            if (winner != "no")
                ans = "yes";
            else
                ans = "no";
        }

        if (req.find("card") != std::string::npos)
        {
            if (index != -1 && Card::effect(req, rooms[index].getPlayer(p.playerID).resources, rooms[index].getEnemy(p.playerID).resources))
                ans = "success";
            else
                ans = "no";
            if (ans == "success")
            {
                ans = "done";
                if (rooms[index].turn == 1)
                {
                    rooms[index].turn = 0;
                }
                else
                    rooms[index].turn = 1;
                rooms[index].modified = true;
            }
        }
        if (write(p.playerDescriptor, ans.c_str(), ans.size()) < 0)
        {
            perror("[SERVER]Error while sending the response ! Error \n");
        }

        // secondary communication
        if (req.find("card") != std::string::npos)
        {
            if (ans != "no")
            {
                serialize(rooms[index].getPlayer(p.playerID).resources);
                if (write(p.playerDescriptor, &rooms[index].getPlayer(p.playerID).resources, sizeof(Resources)) < 0)
                {
                    perror("[SERVER]Error while sending the response ! Error \n");
                }
                desirealize(rooms[index].getPlayer(p.playerID).resources);

                serialize(rooms[index].getEnemy(p.playerID).resources);
                if (write(p.playerDescriptor, &rooms[index].getEnemy(p.playerID).resources, sizeof(Resources)) < 0)
                {
                    perror("[SERVER]Error while sending the response ! Error \n");
                }
                desirealize(rooms[index].getEnemy(p.playerID).resources);
            }
            rooms[index].getPlayer(p.playerID).resources.bricks += rooms[index].getPlayer(p.playerID).resources.builders;
            rooms[index].getPlayer(p.playerID).resources.crystals += rooms[index].getPlayer(p.playerID).resources.magic;
            rooms[index].getPlayer(p.playerID).resources.weapons += rooms[index].getPlayer(p.playerID).resources.soldiers;
        }
        if (req == "update")
        {
            if (ans != "no")
            {
                serialize(rooms[index].getPlayer(p.playerID).resources);
                if (write(p.playerDescriptor, &rooms[index].getPlayer(p.playerID).resources, sizeof(Resources)) < 0)
                {
                    perror("[SERVER]Error while sending the response ! Error \n");
                }
                desirealize(rooms[index].getPlayer(p.playerID).resources);

                serialize(rooms[index].getEnemy(p.playerID).resources);
                if (write(p.playerDescriptor, &rooms[index].getEnemy(p.playerID).resources, sizeof(Resources)) < 0)
                {
                    perror("[SERVER]Error while sending the response ! Error \n");
                }
                desirealize(rooms[index].getEnemy(p.playerID).resources);
            }
        }
        if (req == "create-room")
        {
            char owner[101];
            if (read(p.playerDescriptor, owner, 101) < 0)
            {
                perror("[SERVER]Error while reading the owner name ! Error \n");
            }
            Room a(owner, roomIDS);
            a.player1 = p;
            a.player1.orderInRoom = 1;
            a.player1.playerName = owner;
            roomIDS++;
            rooms.push_back(a);
        }
        if (req == "get-rooms")
        {
            char message[101];
            if (read(p.playerDescriptor, message, 101) < 0)
            {
                perror("[SERVER]Error while reading the message ! Error \n");
            }
            else
            {
                std::string roomsNr = std::to_string(rooms.size());
                char rNr[101];
                strcpy(rNr, roomsNr.c_str());

                if (write(p.playerDescriptor, &rNr, roomsNr.size()) < 0)
                {
                    perror("[SERVER]Error while sending the response ! Error \n");
                }
                for (int i = 0; i < rooms.size(); i++)
                {
                    if (read(p.playerDescriptor, message, 101) < 0)
                    {
                        perror("[SERVER]Error while reading the message ! Error \n");
                    }
                    else
                    {
                        if (write(p.playerDescriptor, rooms[i].name.c_str(), rooms[i].name.size()) < 0)
                        {
                            perror("[SERVER]Error while sending the response ! Error \n");
                        }
                    }
                }
            }
        }
        if (req.find("join-room") != std::string::npos)
        {
            char name[101];
            char enemyName[101];
            bzero(name, 101);
            bzero(enemyName, 101);
            if (read(p.playerDescriptor, name, 101) < 0)
            {
                perror("[SERVER]Error while reading the message ! Error \n");
            }
            std::string roomName = (req.c_str()) + 10;
            for (int i = 0; i < rooms.size(); i++)
                if (roomName == rooms[i].name)
                {
                    rooms[i].player2.playerName = name;
                    strcpy(enemyName, rooms[i].player1.playerName.c_str());
                }

            if (write(p.playerDescriptor, enemyName, strlen(enemyName)) < 0)
            {
                perror("[SERVER]Error while sending the response ! Error \n");
            }
        }
        if (req == "has-enemy-joined")
        {
            if (ans == "yes")
            {
                if (write(p.playerDescriptor, rooms[index].getEnemy(p.playerID).playerName.c_str(), rooms[index].getEnemy(p.playerID).playerName.size()) < 0)
                {
                    perror("[SERVER]Error while sending the response ! Error \n");
                }
            }
        }
        if (req == "game-over")
        {
            if (ans != "no")
            {
                std::string winner = gameOver(rooms[index].getPlayer(p.playerID), rooms[index].getEnemy(p.playerID));
                if (write(p.playerDescriptor, winner.c_str(), winner.size()) < 0)
                {
                    perror("[SERVER]Error while sending the response ! Error \n");
                }
            }
        }
    }
}

void *player(void *args)
{
    int id = *(int *)(args);
    int index = -1;
    Player p;
    for (int i = 0; i < Server::players.size(); i++)
        if (Server::players[i].playerID == id)
        {
            p = Server::players[i];
            index = i;
            break;
        }

    do // cat timp e conectat
    {
        Server::getInstance().getRequest(p, index);
    } while (Server::players[index].state == Player::IN_GAME);

    if (Server::players[index].state == Player::DISCONNECTED)
    {
        int roomIndex = -1;
        for (int i = 0; i < Server::rooms.size(); i++)
        {
            if (p.playerID == Server::rooms[i].player1.playerID || p.playerID == Server::rooms[i].player2.playerID)
            {
                roomIndex = i;
                break;
            }
        }
        Bot bot(Server::rooms[roomIndex].getPlayer(p.playerID).resources);
        while (Server::rooms[roomIndex].getEnemy(p.playerID).state != Player::GAME_OVER)
        {
            sleep(3);
            bot.resources = Server::rooms[roomIndex].getPlayer(p.playerID).resources;
            if (Server::rooms[roomIndex].turn != (Server::rooms[roomIndex].getEnemy(p.playerID).orderInRoom % 2))
            {
                std::string ans;
                if (Card::effect(bot.pickCard(), bot.resources, Server::rooms[roomIndex].getEnemy(p.playerID).resources))
                    ans = "success";

                if (Server::rooms[roomIndex].turn == 1)
                {
                    Server::rooms[roomIndex].turn = 0;
                }
                else
                    Server::rooms[roomIndex].turn = 1;
                Server::rooms[roomIndex].modified = true;

                bot.resources.bricks += bot.resources.builders;
                bot.resources.crystals += bot.resources.magic;
                bot.resources.weapons += bot.resources.soldiers;

                Server::rooms[roomIndex].getPlayer(p.playerID).resources = bot.resources;
            }
        }
    }
}

void Server::run()
{
    if (init() != 0)
    {
        while (1)
        {
            int length = sizeof(client1);

            printf("[SERVER]Waiting at the port %d...\n", PORT);
            fflush(stdout);

            int clientDescriptor = accept(serverDescriptor, (sockaddr *)&client1, (socklen_t *)&length);

            if (clientDescriptor < 0)
            {
                perror("[SERVER]Connection error! Error : \n");
                continue;
            }
            else
            {
                ID++;
                Player p(clientDescriptor, ID);
                players.emplace_back(p);
                pthread_create(&p.thread, NULL, &player, &ID);
            }
        }
    }
}

int Server::init()
{
    if ((serverDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("[SERVER]Could not create server socket! Error : \n");
        return errno;
    }

    bzero(&server, sizeof(server));
    bzero(&client1, sizeof(client1));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    if (bind(serverDescriptor, (sockaddr *)&server, sizeof(sockaddr)) == -1)
    {
        perror("[SERVER]Could not bind the server socket! Error \n");
        return errno;
    }

    if (listen(serverDescriptor, 5) == -1)
    {
        perror("[SERVER]Listen error.Error \n");
        return errno;
    }

    return 1;
}