#ifndef CLIENT_CARD_H
#define CLIENT_CARD_H

#include "Includes.h"
#include "Resources.h"

class Card
{
private:
    int cost;
    std::string costResource;
    std::string name;
    std::string effect;
    std::string secondaryEffect;
    int xPos, yPos;
    static int cardID;
    bool resAvailable(Resources player);

public:
    Card();
    void draw(Resources player);

    void setName(std::string n){name = n;};
    void setPos(int x, int y){xPos = x; yPos = y;};

    int getX(){return xPos;};
    int getY(){return yPos;};
    std::string getName(){return name;};
    void setupCard(int r);
};


#endif
