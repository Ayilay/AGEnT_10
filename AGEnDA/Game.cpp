#include "Game.h"

Game::Game()
{

}

void Game::playGame(int type)
{
    switch(type)
    {
        case KOTH:
            playKOTH();
        case CSGO:
            playCSGO();
        default:
            return;
    }
}

void Game::playKOTH()
{

}

void Game::playCSGO()
{

}
