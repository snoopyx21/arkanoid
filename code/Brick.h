#ifndef BRICK_H_
#define BRICK_H_

#include "Mobject.h"

#define OFFSET_GRID_X 32
#define OFFSET_GRID_Y 32


class Brick: public Mobject
{
    public:
        // attributs
        int id;
        int life;
        int score;
        int posx;
        int posy;
        int offset;
        SDL_Rect vBrick;
        SDL_Rect srcBrick;
        int state;
        int touched;
        /* For brick 12 and 13 */
        
        // methodes
        Brick(SDL_Surface* win, SDL_Surface* sprite, int i, int j);
        ~Brick();
	    void update();
	    void view();
        void init(int bid, int difficulty);
};

#endif