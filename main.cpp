#include <Circle.hpp>
#include <Game.hpp>
#include <SFML/Graphics.hpp>
int main()
{
    srand(time(0));
    msp::Game game(1000, 600, "Game");
    game.Setup_Circle();

    game.LifeCycle();

    return 0;
}