#include "Game.h"

int main(int argc, char* argv[]) 
{
    // Create the game object
    Game* game = new Game();
    // Initialize and run the game
    if (game->init()) 
    {
        game->run();
        game->clean_up();
    }
    // Clean up
    delete game;
    return 0;
}

