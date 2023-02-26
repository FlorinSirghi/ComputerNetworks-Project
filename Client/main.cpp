#include <iostream>
#include "Client.h"

int main()
{
    char adress[101];
    char port[101];

    std::cout << "Introduceti adresa : \n";
    std::cin >> adress;
    std::cout << "Introduceti portul: \n";
    std::cin >> port;

    Client cl = Client::getInstance();
    if(cl.init(adress, port))
        cl.run();
    return 0;
}
