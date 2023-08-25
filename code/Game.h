#ifndef GAME_H_
#define GAME_H_

#include "SDL.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector> 
#include <memory> 

#include "Grille.h"
#include "Vaus.h"
#include "Ball.h"
#include "Player.h"
#include "WriteManager.h"
#include "Bonus.h"

using namespace std;

#define FPS_DELAY       20 //given in arkanoid.cpp
#define GAME_WIDTH      482
#define GAME_HEIGTH     596
#define RANDOM_NUMBER   8

class Game 
{
    public:
        // methodes 
        Game();
        ~Game();

        bool init();
        void run();
        void clean_up();

    private:
        // attributs 
        SDL_Window* window;
        SDL_Surface* win_surf;// RENDERER AND SURFACE AND TEXTURE to be easier
        SDL_Surface* sprites_surf;// RENDERER AND SURFACE AND TEXTURE to be easier
        
        Grille* grid;
        Vaus* vaus;
        Ball* ball;
        Player* player;
        Player* player1;
        WriteManager* wtMan;
        vector<shared_ptr<Vaus>> all_vaus;
        vector<shared_ptr<Ball>> all_ball;
        vector<shared_ptr<Bonus>> all_bonus;
        
        //object wih bonus or point => player for counting point

        int disMenu;
        int mode;
        int firstLevel;
        int bestScore;

        SDL_Rect srcLogo;
        SDL_Rect resLogo;

        // methodes
        void update(int mode);
        void view();

        void menu(int x, int y, int click);
        void newGame(void);//if first first level else next_level
        void boardCollisions(void);
        void vausCollisions(void);
        void brickCollisions(void);
        void bonusCollisions(void);
        void bonusEffect(int bonus_number);
       
};

#endif
