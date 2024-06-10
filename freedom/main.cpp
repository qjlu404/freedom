#include "RayGameCore.h"

int main()
{
    RayGameCore gameCore;
    gameCore.Load();
    sf::Clock clock;

    while (gameCore.windowIsOpen())
    {
        sf::Int32 dt = clock.restart().asMilliseconds() * 2;
        gameCore.windowEvents();
        gameCore.update(dt);
        gameCore.render();
    }
    

    return 0;
}