#include "Bonus.h"

Bonus::Bonus(SDL_Surface* win, SDL_Surface* sprite, float x, float y): Mobject(win,sprite)
{
	width 			= BONUS_WIDTH;
    height 			= BONUS_HEIGHT;
	resBonus.x 		= x;
	resBonus.y 		= y;
	srcBonus.w 		= width;
	srcBonus.h 		= height;
	this->x 		= resBonus.x;
	this->y 		= resBonus.y;
	active			= 0;
	state			= 0;
}

Bonus::~Bonus()
{
}

void Bonus::init(int bonus_id) 
{
	id = bonus_id;
	switch(id)
	{
		case 0 :
			srcBonus.x 		= OFFSET_BONUS_X;
			srcBonus.y 		= OFFSET_BONUS_Y + id*height;
			break;
		case 1 :
			srcBonus.x 		= OFFSET_BONUS_X;
			srcBonus.y 		= OFFSET_BONUS_Y + id*height;
			break;
		case 2 :
			srcBonus.x 		= OFFSET_BONUS_X;
			srcBonus.y 		= OFFSET_BONUS_Y + id*height;
			break;
		case 3 :
			srcBonus.x 		= OFFSET_BONUS_X;
			srcBonus.y 		= OFFSET_BONUS_Y + id*height;
			break;
		case 4 :
			srcBonus.x 		= OFFSET_BONUS_X;
			srcBonus.y 		= OFFSET_BONUS_Y + id*height;
			break;
		case 5 :
			srcBonus.x 		= OFFSET_BONUS_X;
			srcBonus.y 		= OFFSET_BONUS_Y + id*height;
			break;
		case 6 :
			srcBonus.x 		= OFFSET_BONUS_X;
			srcBonus.y 		= OFFSET_BONUS_Y + id*height;
			break;
		default:
			break;
	}
}

void Bonus::update() 
{
	active = 1;
}

void Bonus::view()
{
	if(active)
	{
		srcBonus.x = OFFSET_BONUS_X + state*width;
		SDL_BlitSurface(sprite, &srcBonus, win, &resBonus);
		state = (state+1)%BONUS_STATE;
		resBonus.y+=5;
		y = resBonus.y;
	}
}

