#include "Player.h"

Player::Player()
{
    life            = 3;
    score           = 0;
    level           = 1;
    difficulty      = 0;
    current_bonus   = 0;
}
Player::~Player()
{
    
}

void Player::gainBonus(int bonus)
{
    current_bonus = bonus;
}

void Player::gainLife()
{
    life++;
}

void Player::next_level()
{
    current_bonus = 0;
    if (level < NB_LEVELS)
    {
        level++;
        if(level > ROUND3)
        {
            difficulty = 3;
        }
        else if (level > ROUND2)
        {
            difficulty = 2;
        }
        else if(level > ROUND1)
        {
            difficulty = 1;
        }
    }
    else
    {
        /* victoire : affichage victoire - print score_total */
    }
}

void Player::refresh()
{
    life            = 3;
    score           = 0;
    level           = 1;
    difficulty      = 0;
    current_bonus   = 0;
}
