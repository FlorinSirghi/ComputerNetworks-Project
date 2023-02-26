#ifndef SERVER_BOT_H
#define SERVER_BOT_H

#include "Includes.h"
#include "Resources.h"

class Bot
{
public:
    Resources resources;
    Bot(Resources r)
    {
        resources = r;
    }
    std::string pickCard()
    {
        srand(time(0));
        std::vector<std::string> cards = 
        {
             "card_Wall",
             "card_Base",
             "card_Defence",
             "card_Reserve",
             "card_Tower",
             "card_School",
             "card_Wain",
             "card_Fence",
             "card_Fort",
             "card_Babylon",
             "card_Archer",
             "card_Knight",
             "card_Rider",
             "card_Platoon",
             "card_Recruit",
             "card_Attack",
             "card_Saboteur",
             "card_Thief",
             "card_Swat",
             "card_Banshee",
             "card_Conjure bricks",
             "card_Conjure crystals",
             "card_Conjure weapons",
             "card_Crush bricks",
             "card_Crush crystals",
             "card_Crush weapons",
             "card_Sorcerer",
             "card_Dragon",
             "card_Pixies",
             "card_Curse"
        };
        return (cards[rand() % 30]);
    }

};

#endif