#include "Game.h"

int main()
{
    Game& game = Game::getInstance();

    game.init();

    game.runGame();

    game.deleteGame();
    return 0;
}
