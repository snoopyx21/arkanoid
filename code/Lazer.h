#ifndef LAZER_H_
#define LAZER_H_

#include "Mobject.h"

#define LAZER_WIDTH      10
#define LAZER_HEIGHT     10



class Lazer: public Mobject 
{
	public:
		// methodes
		Lazer(SDL_Surface* win, SDL_Surface* sprite);
	    ~Lazer();
	    void update();
	    void view();

		// attributs
	    SDL_Rect srcLazer;
	    SDL_Rect resLazer;


};
