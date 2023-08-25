#ifndef HARMFUL_H_
#define HARMFUL_H_

#include "Mobject.h"

#define HARMFUL_WIDTH      32
#define HARMFUL_HEIGHT     32



class Harmful: public Mobject 
{
	public:
		// methodes
		Harmful(SDL_Surface* win, SDL_Surface* sprite);
	    ~Harmful();
	    void update();
	    void view();
	    void setDirection();

		// attributs
	    int type;
	    int touched;
	    int state;
	    float dirx, diry; /*speed in arkanoid.cpp*/
	    float speed;
	    SDL_Rect srcHarmful;
	    SDL_Rect resHarmful;


};

#endif