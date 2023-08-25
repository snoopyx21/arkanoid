#include "Mobject.h"

Mobject::Mobject(SDL_Surface* win_sur, SDL_Surface* sprites_sur) 
{
    x = 0;
    y = 0;
    width = 1;
    height = 1;
	win = win_sur;
	sprite = sprites_sur;
}

Mobject::~Mobject() 
{
}

void Mobject::update() 
{
}

void Mobject::view() //use the SDL_function => SDL_blit or renderer?? rendere easier not need to have full surface
{
}

bool Mobject::collision(Mobject* other) 
{
    if ((other->x <= x + width && x <= other->x + other->width) 
        &&
        (other->y <= y + (height) && y <= other->y + other->height)) 
    {
        return true;
    }
    return false;
}