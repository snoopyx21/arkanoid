#include "Brick.h"

Brick::Brick(SDL_Surface* win, SDL_Surface* sprite, int i, int j): Mobject(win,sprite)
{
	width 			= 32;
    height 			= 16;
	vBrick.x 		= OFFSET_GRID_X + j*width;
	vBrick.y 		= OFFSET_GRID_Y + i*height;
	srcBrick.w 		= width;
	srcBrick.h 		= height;
	x 				= vBrick.x;
	y 				= vBrick.y;
    life 			= 0;
	score 			= 0;
	state			= 0;
	touched			= 0;
	offset			= 0;
}

Brick::~Brick()
{
}

void Brick::init(int bid, int difficulty) 
{
	id = bid;
	life = 0;
	if(id != -1)
	{
		offset = id;
		switch(id)
		{
			case 0 :
				score 	= 50;
				life	= 1;
				break;
			case 1 :
				score 	= 50;
				life	= 1;
				break;
			case 2 :
				score 	= 60;
				life	= 1;
				break;
			case 3 :
				score 	= 60;
				life	= 1;
				break;
			case 4 :
				score 	= 70;
				life	= 1;
				break;
			case 5 :
				score 	= 80;
				life	= 1;
				break;
			case 6 :
				score 	= 90;
				life	= 1;
				break;
			case 7 :
				score 	= 100;
				life	= 1;
				break;
			case 8 :
				score 	= 110;
				life	= 1;
				break;
			case 9 :
				score 	= 110;
				life	= 1;
				break;
			case 10 :
				score 	= 110;
				life	= 1;
				break;
			case 11 :
				score 	= 110;
				life	= 1;
				break;
			case 12: // hard wall
				score	= 120;
				switch(difficulty)
				{
					case 0 :
						life	= 2;
						break;
					case 1 :
						life	= 3;
						break;
					case 2 :
						life	= 4;
						break;
					case 3 :
						life	= 5;
						break;
					default :
						life	= 2;
						break;
				}
				break;
			case 13: //indestructible
				offset	= 18;
				life	= -1;
				break;
			default:
				life	= 1;
				break;
		}
		srcBrick.x = (offset%6)*width;
		srcBrick.y = (offset/6)*height;
	}
}

void Brick::update() 
{
}

void Brick::view()
{
	if(touched)
	{
		if(state < 5)
		{
			srcBrick.x = (offset%6)*width + state*width;
			state++;
		}
		else
		{
			touched = 0;
			state = 0;
			srcBrick.x = (offset%6)*width;
		}
	}
	SDL_BlitSurface(sprite, &srcBrick, win, &vBrick);
}