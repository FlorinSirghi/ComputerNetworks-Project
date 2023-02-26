//
// Created by florin on 01.12.2022.
//

#ifndef SERVER_CARD_H
#define SERVER_CARD_H

#include "Includes.h"
#include "Resources.h"

class Card
{
public:
    static bool effect(std::string cardCode, Resources &player1, Resources &player2)
    {
        bool success = true;
        if(cardCode == "card_Wall")
        {
            if(player1.bricks >= 1)
            {
                player1.fence += 3;
                player1.bricks -= 1;
            }
            else
                success = false;
        }
        if(cardCode == "card_Base")
        {
            if(player1.bricks >= 1)
            {
                player1.castle += 2;
                player1.bricks -= 1;
            }
            else
                success = false;
        }
        if(cardCode == "card_Defence")
        {
            if(player1.bricks >= 3)
            {
                player1.fence += 6;
                player1.bricks -= 3;
            }
            else
                success = false;
        }
        if(cardCode == "card_Reserve")
        {
            if(player1.bricks >= 3 && player1.fence >= 4)
            {
                player1.castle += 8;
                player1.fence -= 4;
                player1.bricks -= 3;
            }
            else
                success = false;
        }
        if(cardCode == "card_Tower")
        {
            if(player1.bricks >= 5)
            {
                player1.castle += 5;
                player1.bricks -= 5;
            }
            else
                success = false;
        }
        if(cardCode == "card_School")
        {
            if(player1.bricks >= 8)
            {
                player1.builders += 1;
                player1.bricks -= 8;
            }
            else
                success = false;
        }
        if(cardCode == "card_Wain")
        {
            if(player1.bricks >= 10)
            {
                player1.castle += 8;
                player2.castle -= std::min(4, player2.castle);
                player1.bricks -= 10;
            }
            else
                success = false;
        }
        if(cardCode == "card_Fence")
        {
            if(player1.bricks >= 12)
            {
                player1.fence += 22;
                player1.bricks -= 12;
            }
            else
                success = false;
        }
        if(cardCode == "card_Fort")
        {
            if(player1.bricks >= 18)
            {
                player1.castle += 20;
                player1.bricks -= 18;
            }
            else
                success = false;
        }
        if(cardCode == "card_Babylon")
        {
            if(player1.bricks >= 39)
            {
                player1.castle += 32;
                player1.bricks -= 39;
            }
            else
                success = false;
        }
        if(cardCode == "card_Archer")
        {
            if(player1.weapons >= 1)
            {
                int attack = 2;
                int initFence = player2.fence;
                player2.fence = std::max(0, player2.fence - attack);
                attack -= (initFence - player2.fence);

                player2.castle -= attack;
                player1.weapons -= 1;
            }
            else
                success = false;
        }
        if(cardCode == "card_Knight")
        {
            if(player1.weapons >= 2)
            {
                int attack = 3;
                int initFence = player2.fence;
                player2.fence = std::max(0, player2.fence - attack);
                attack -= (initFence - player2.fence);

                player2.castle -= attack;
                player1.weapons -= 2;
            }
            else
                success = false;
        }
        if(cardCode == "card_Rider")
        {
            if(player1.weapons >= 2)
            {
                int attack = 4;
                int initFence = player2.fence;
                player2.fence = std::max(0, player2.fence - attack);
                attack -= (initFence - player2.fence);

                player2.castle -= attack;
                player1.weapons -= 2;
            }
            else
                success = false;
        }
        if(cardCode == "card_Platoon")
        {
            if(player1.weapons >= 4)
            {
                int attack = 6;
                int initFence = player2.fence;
                player2.fence = std::max(0, player2.fence - attack);
                attack -= (initFence - player2.fence);

                player2.castle -= attack;
                player1.weapons -= 4;
            }
            else
                success = false;
        }
        if(cardCode == "card_Recruit")
        {
            if(player1.weapons >= 8)
            {
                player1.soldiers += 1;
                player1.weapons -= 8;
            }
            else
                success = false;
        }
        if(cardCode == "card_Attack")
        {
            if(player1.weapons >= 10)
            {
                int attack = 12;
                int initFence = player2.fence;
                player2.fence = std::max(0, player2.fence - attack);
                attack -= (initFence - player2.fence);

                player2.castle -= attack;
                player1.weapons -= 10;
            }
            else
                success = false;
        }
        if(cardCode == "card_Saboteur")
        {
            if(player1.weapons >= 12)
            {
                player2.bricks = std::max(0, player2.bricks - 4);
                player2.weapons = std::max(0, player2.weapons - 4);
                player2.crystals = std::max(0, player2.crystals - 4);

                player1.weapons -= 12;
            }
            else
                success = false;
        }
        if(cardCode == "card_Thief")
        {
            if(player1.weapons >= 15)
            {
                player1.bricks += std::min(5, player2.bricks);
                player1.weapons += std::min(5, player2.weapons);
                player1.crystals += std::min(5, player2.crystals);
                player2.bricks -= std::max(0, player2.bricks - 5);
                player2.weapons -= std::max(0, player2.weapons - 5);
                player2.crystals -= std::max(0, player2.crystals - 5);

                player1.weapons -= 15;
            }
            else
                success = false;
        }
        if(cardCode == "card_Swat")
        {
            if(player1.weapons >= 18)
            {
                player2.castle -= 10;
                player1.weapons -= 18;
            }
            else
                success = false;
        }
        if(cardCode == "card_Banshee")
        {
            if(player1.weapons >= 28)
            {
                int attack = 32;
                int initFence = player2.fence;
                player2.fence = std::max(0, player2.fence - attack);
                attack -= (initFence - player2.fence);
                player2.castle -= attack;

                player1.weapons -= 28;
            }
            else
                success = false;
        }

        if(cardCode == "card_Conjure bricks")
        {
            if(player1.crystals >= 4)
            {
                player1.bricks += 8;
                player1.crystals -= 4;
            }
            else
                success = false;
        }

        if(cardCode == "card_Conjure crystals")
        {
            if(player1.crystals >= 4)
            {
                player1.crystals += 8;
                player1.crystals -= 4;
            }
            else
                success = false;
        }

        if(cardCode == "card_Conjure weapons")
        {
            if(player1.crystals >= 4)
            {
                player1.weapons += 8;
                player1.crystals -= 4;
            }
            else
                success = false;
        }

        if(cardCode == "card_Crush bricks")
        {
            if(player1.crystals >= 4)
            {
                player2.bricks = std::max(0, player2.bricks - 8);
                player1.crystals -= 4;
            }
            else
                success = false;
        }
        if(cardCode == "card_Crush crystals")
        {
            if(player1.crystals >= 4)
            {
                player2.crystals = std::max(0, player2.crystals - 8);
                player1.crystals -= 4;
            }
            else
                success = false;
        }

        if(cardCode == "card_Crush weapons")
        {
            if(player1.crystals >= 4)
            {
                player2.weapons = std::max(0, player2.weapons - 8);
                player1.crystals -= 4;
            }
            else
                success = false;
        }

        if(cardCode == "card_Sorcerer")
        {
            if(player1.crystals >= 8)
            {
                player1.magic += 1;
                player1.crystals -= 8;
            }
            else
                success = false;
        }

        if(cardCode == "card_Dragon")
        {
            if(player1.crystals >= 21)
            {
                int attack = 25;
                int initFence = player2.fence;
                player2.fence = std::max(0, player2.fence - attack);
                attack -= (initFence - player2.fence);
                player2.castle -= attack;

                player1.crystals -= 21;
            }
            else
                success = false;
        }

        if(cardCode == "card_Pixies")
        {
            if(player1.crystals >= 22)
            {
                player1.castle += 22;
                player1.crystals -= 22;
            }
            else
                success = false;
        }

        if(cardCode == "card_Curse")
        {
            if(player1.crystals >= 45)
            {
                player1.bricks += 1;
                player1.builders += 1;
                player1.weapons += 1;
                player1.soldiers += 1;
                player1.crystals += 1;
                player1.magic += 1;
                player1.fence += 1;
                player1.castle += 1;

                player2.bricks = std::max(0, player2.bricks - 1);
                player2.builders = std::max(0, player2.builders - 1);
                player2.weapons = std::max(0, player2.weapons - 1);
                player2.soldiers = std::max(0, player2.soldiers - 1);
                player2.crystals = std::max(0, player2.crystals - 1);
                player2.magic = std::max(0, player2.magic - 1);
                player2.fence = std::max(0, player2.fence - 1);
                player2.castle = std::max(0, player2.castle - 1);

                player1.crystals -= 45;
            }
            else
                success = false;
        }

        return success;
    }
};


#endif
