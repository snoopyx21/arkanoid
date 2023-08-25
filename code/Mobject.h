#ifndef MOBJECT_H_
#define MOBJECT_H_

#include "SDL.h"
/*
Moving object
Ball and Vaus
*/
class Mobject 
{
	public:
	    Mobject(SDL_Surface* win_sur, SDL_Surface* sprites_sur);
	    virtual ~Mobject();
	    SDL_Surface* win;
	    SDL_Surface* sprite;

	    float x, y, width, height;

	    virtual void update();
	    virtual void view();

	    bool collision(Mobject* other);
};

#endif
