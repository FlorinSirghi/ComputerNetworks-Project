#include "Server.h"

int main()
{
    Server sv = Server::getInstance();
    sv.run();
    return 0;
}