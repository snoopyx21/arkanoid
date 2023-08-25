#include "WriteManager.h"

WriteManager::WriteManager(SDL_Surface* win_sur, SDL_Surface* sprite_sur)
{
	win = win_sur;
	sprite = sprite_sur;
}

WriteManager::~WriteManager()
{
}

void WriteManager::writeOnSurf(std::string label, int lx, int ly)
{
	int asciiVal;

    SDL_Rect srcLetter;
    srcLetter.w = LETTER_W;
    srcLetter.h = LETTER_H;


    SDL_Rect resLetter;

    resLetter.w = LETTER_W;
    resLetter.h = LETTER_H;
    resLetter.x = lx;
    resLetter.y = ly;

    for(int i= 0; i < label.size();i++)
    {

    	if(label[i] >= FIRST_C && label[i] <= LAST_C)
    	{
    		asciiVal = label[i] - FIRST_C;
    		srcLetter.x = WMANAGER_X + (asciiVal%NB_LETTER)*LETTER_W;
    		srcLetter.y = WMANAGER_Y + (asciiVal/NB_LETTER)*LETTER_H;
	    	SDL_BlitSurface(sprite, &srcLetter, win, &resLetter);
	    	resLetter.x += 16;
    	}
    }
}