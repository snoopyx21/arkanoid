#ifndef BONUS_H_
#define BONUS_H_

#include "Mobject.h"

#define OFFSET_BONUS_X 256
#define OFFSET_BONUS_Y 0

#define BONUS_HEIGHT 16
#define BONUS_WIDTH 32

#define BONUS_STATE 8


class Bonus: public Mobject
{
    public:
        // attributs
        int id; // from 0 to 6
        int active; // 0 when not active and 1 when the brick above the bonus is broken
        int state; // from 0 to 7
        SDL_Rect resBonus;
        SDL_Rect srcBonus;
        
        // methodes
        Bonus(SDL_Surface* win, SDL_Surface* sprite, float i, float j);
        ~Bonus();

        void update();

	    void view();
        void init(int bonus_id);
};

#endif