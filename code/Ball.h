#ifndef BALL_H_
#define BALL_H_

#include "Mobject.h"

#include <math.h>

#define REDUCTION_SPEED 0.8
#define SPEED_BALL 		15
#define BALL_WIDTH      18
#define BALL_HEIGHT     15
#define BALL_INITIAL_X 	232
#define BALL_INITIAL_Y 	544


class Ball: public Mobject 
{
	public:
		// methodes
		Ball(SDL_Surface* win, SDL_Surface* sprite);
	    ~Ball();
	    void update();
	    void view();
	    void setDirection();
		void reduceSpeed();
		void ballCatch();
		void shot();
		void normalSpeed();
		void setCoor(float bx, float by);
		void setDefault();

		// attributs
	    int type;
	    int catched;
	    float dirx, diry; /*speed in arkanoid.cpp*/
	    float speed;
	    SDL_Rect srcBall;
	    SDL_Rect res_ball;


};

#endif
