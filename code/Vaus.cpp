#include "Vaus.h"

Vaus::Vaus(SDL_Surface* win, SDL_Surface* sprite): Mobject(win,sprite)
{
	type = 0;
    actualWidth = 0;
	width = vaus_width[actualWidth];//Width of the first VAUS
    height = VAUS_HEIGHT;
    scrVaus.x = POSX;
	scrVaus.h = height; 
    x = VAUS_INITIAL_X;
    y = VAUS_INITIAL_Y;
}

Vaus::~Vaus() 
{
}


void Vaus::update() 
{
}

void Vaus::view() 
{
    scrVaus.y = 128 + type*height;
    scrVaus.w = width;
    SDL_Rect dest = {(int)x,(int)y,0,0};
    SDL_BlitSurface(sprite, &scrVaus, win, &dest);
}

void Vaus::upgradeVaus()
{
    if(actualWidth < MAX_VAUS_WIDTH)
    {
        /* width modifié et donc srcVaus.w */
        actualWidth++;
        type++;
        width = vaus_width[actualWidth];
    }
}

void Vaus::normalVaus()
{
    actualWidth = 0;
    type = 0;
}


void Vaus::setDefault()
{
    x = VAUS_INITIAL_X;
    y = VAUS_INITIAL_Y;    
}