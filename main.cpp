#include <SFML/Graphics.hpp>
#include <Game.hpp>
#include <Circle.hpp>
int main() {
    srand(time(0));
    msp::Game game(1000, 600,10, "Game");
    game.LifeCycle();
    return 0;
}
