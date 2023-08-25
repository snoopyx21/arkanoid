#ifndef VAUS_H_
#define VAUS_H_

#define POSX 384
#define MAX_VAUS_WIDTH 	7
#define VAUS_HEIGHT     16
#define VAUS_INITIAL_X 	211
#define VAUS_INITIAL_Y 	560

#include "Mobject.h"

static const int vaus_width[] = {60,70,80,90,98,108,118,128};

class Vaus: public Mobject 
{
	public:
	    Vaus(SDL_Surface* win, SDL_Surface* sprite);
	    ~Vaus();

	    int type;
		int actualWidth;
	    SDL_Rect scrVaus;

	    void update();
	    void view();
		void upgradeVaus();
		void normalVaus();
		void setDefault();

};

#endif