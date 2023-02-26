#include "Card.h"

int Card::cardID = 0;

Card::Card()
{
    secondaryEffect = "";
}

void Card::setupCard(int r)
{
    effect = "";
    secondaryEffect = "";
    if(r == 0)
    {
        name = "card_Wall";
        cost = 1;
        costResource = "bricks";
        effect = "fence + 3";
    }

    if(r == 1)
    {
        name = "card_Base";
        cost = 1;
        costResource = "bricks";
        effect = "castle + 2";
    }

    if(r == 2)
    {
        name = "card_Defence";
        cost = 3;
        costResource = "bricks";
        effect = "fence + 6";
    }

    if(r == 3)
    {
        name = "card_Reserve";
        cost = 3;
        costResource = "bricks";
        effect = "castle + 8";
        secondaryEffect = "fence - 4";
    }

    if(r == 4)
    {
        name = "card_Tower";
        cost = 5;
        costResource = "bricks";
        effect = "castle + 5";
    }

    if(r == 5)
    {
        name = "card_School";
        cost = 8;
        costResource = "bricks";
        effect = "builders + 1";
    }

    if(r == 6)
    {
        name = "card_Wain";
        cost = 10;
        costResource = "bricks";
        effect = "castle + 8";
        secondaryEffect = "enemy castle-4";
    }

    if(r == 7)
    {
        name = "card_Fence";
        cost = 12;
        costResource = "bricks";
        effect = "fence + 22";
    }

    if(r == 8)
    {
        name = "card_Fort";
        cost = 18;
        costResource = "bricks";
        effect = "castle + 20";
    }

    if(r == 9)
    {
        name = "card_Babylon";
        cost = 39;
        costResource = "bricks";
        effect = "castle + 32";
    }

    if(r == 10)
    {
        name = "card_Archer";
        cost = 1;
        costResource = "weapons";
        effect = "attack 2";
    }

    if(r == 11)
    {
        name = "card_Knight";
        cost = 2;
        costResource = "weapons";
        effect = "attack 3";
    }

    if(r == 12)
    {
        name = "card_Rider";
        cost = 2;
        costResource = "weapons";
        effect = "attack 4";
    }

    if(r == 13)
    {
        name = "card_Platoon";
        cost = 4;
        costResource = "weapons";
        effect = "attack 6";
    }

    if(r == 14)
    {
        name = "card_Recruit";
        cost = 8;
        costResource = "weapons";
        effect = "soldiers + 1";
    }

    if(r == 15)
    {
        name = "card_Attack";
        cost = 10;
        costResource = "weapons";
        effect = "attack 12";
    }

    if(r == 16)
    {
        name = "card_Saboteur";
        cost = 12;
        costResource = "weapons";
        effect = "enemy";
        secondaryEffect = "stocks - 4";
    }

    if(r == 17)
    {
        name = "card_Thief";
        cost = 15;
        costResource = "weapons";
        effect = "transfer enemy";
        secondaryEffect = "5 stocks";
    }

    if(r == 18)
    {
        name = "card_Swat";
        cost = 18;
        costResource = "weapons";
        effect = "enemy";
        secondaryEffect = "castle - 10";
    }

    if(r == 19)
    {
        name = "card_Banshee";
        cost = 28;
        costResource = "weapons";
        effect = "attack 32";
    }

    if(r == 20)
    {
        name = "card_Conjure bricks";
        cost = 4;
        costResource = "crystals";
        effect = "bricks + 8";
    }

    if(r == 21)
    {
        name = "card_Conjure crystals";
        cost = 4;
        costResource = "crystals";
        effect = "crystals + 8";
    }

    if(r == 22)
    {
        name = "card_Conjure weapons";
        cost = 4;
        costResource = "crystals";
        effect = "weapons + 8";
    }

    if(r == 23)
    {
        name = "card_Crush bricks";
        cost = 4;
        costResource = "crystals";
        effect = "enemy";
        secondaryEffect = "bricks - 8";
    }

    if(r == 24)
    {
        name = "card_Crush crystals";
        cost = 4;
        costResource = "crystals";
        effect = "enemy";
        secondaryEffect = "crystals - 8";
    }

    if(r == 25)
    {
        name = "card_Crush weapons";
        cost = 4;
        costResource = "crystals";
        effect = "enemy";
        secondaryEffect = "weapons - 8";
    }

    if(r == 26)
    {
        name = "card_Sorcerer";
        cost = 8;
        costResource = "crystals";
        effect = "magic + 1";
    }

    if(r == 27)
    {
        name = "card_Dragon";
        cost = 21;
        costResource = "crystals";
        effect = "attack 25";
    }

    if(r == 28)
    {
        name = "card_Pixies";
        cost = 22;
        costResource = "crystals";
        effect = "castle + 22";
    }
    if(r == 29)
    {
        name = "card_Curse";
        cost = 45;
        costResource = "crystals";
        effect = "all + 1";
        secondaryEffect = "enemies all-1";
    }
}

bool Card::resAvailable(Resources player)
{
    if(costResource == "bricks")
    {
        if(player.bricks >= cost)
            return true;
    }
    if(costResource == "weapons")
    {
        if(player.weapons >= cost)
            return true;
    }
    if(costResource == "crystals")
    {
        if(player.crystals >= cost)
            return true;
    }
    return false;
}

void Card::draw(Resources player)
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImGuiStyle initStyle = style;
    if(!resAvailable(player))
        style.Colors[ImGuiCol_WindowBg] = ImVec4(100, 100, 100, 0.4);
    ImGui::SetNextWindowPos(ImVec2(xPos, yPos));
    ImGui::SetNextWindowSize(ImVec2(120, 150));
    std::string title = name + "##" + std::to_string(cardID);
    cardID++;
    if(cardID == 10)
    {
        cardID = 0;
    }
    if(ImGui::Begin(title.c_str() + 5, NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
    {
        ImGui::SetNextWindowPos(ImVec2(xPos, yPos));
        ImGui::SetNextWindowSize(ImVec2(120, 150));
        ImGui::Text("Cost:%d%s", cost, costResource.c_str());
        ImGui::Text("Effect : ");
        ImGui::Text("%s", effect.c_str());
        if(secondaryEffect != "")
            ImGui::Text("%s", secondaryEffect.c_str());
    }
    ImGui::End();
    style = initStyle;
}
