#include "Ball.h"

Ball::Ball(SDL_Surface* win, SDL_Surface* sprite): Mobject(win,sprite) 
{
    width       = BALL_WIDTH;
    height      = BALL_HEIGHT;
	type        = 0;
    x           = BALL_INITIAL_X;
    y           = BALL_INITIAL_Y;
    srcBall.y   = 112;
    srcBall.w   = width;
    srcBall.h   = height;
    dirx        = 1;
    diry        = -1;
    speed       = SPEED_BALL; 
    catched     = 0;
}

Ball::~Ball() 
{
}

void Ball::update() 
{
}

void Ball::setCoor(float bx, float by) 
{
    x = bx;
    y = by;    
}

void Ball::setDefault() 
{
    x = BALL_INITIAL_X;
    y = BALL_INITIAL_Y;
    catched = 1;
}

void Ball::view()
{
    srcBall.x = 326 + type*width;
    res_ball.x = (int)x;
    res_ball.y = (int)y;
    SDL_BlitSurface(sprite, &srcBall, win, &res_ball);
}

void Ball::setDirection()
{
    if(!catched)
    {
        float length = sqrt(dirx * dirx + diry * diry);
        x += speed*(dirx / length);
        y += speed*(diry / length);       
    }

}

void Ball::reduceSpeed()
{
    speed = speed * REDUCTION_SPEED;
}

void Ball::normalSpeed()
{
    speed = SPEED_BALL;
}

void Ball::ballCatch()
{
    catched = 1;
}

void Ball::shot()
{
    catched = 0;
}