#ifndef WRITEMANAGER_H_
#define WRITEMANAGER_H_

#include <string> 
#include "SDL.h"

#define FIRST_C 32
#define LAST_C 127
#define WMANAGER_X 0
#define WMANAGER_Y 504
#define NB_LETTER 16
#define LETTER_W 32
#define LETTER_H 32

class WriteManager 
{
	public:
		WriteManager(SDL_Surface* win, SDL_Surface* sprite);
	    ~WriteManager();
		void writeOnSurf(std::string label, int lx, int ly);

	    SDL_Surface* win;
	    SDL_Surface* sprite;
};

#endif
