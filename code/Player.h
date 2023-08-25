#ifndef PLAYER_H_
#define PLAYER_H_

#define NB_LEVELS       33
#define ROUND1          8  // hit 2 time
#define ROUND2          16 // hit 3 time
#define ROUND3          24 // hit 4 time

#define SCORE_WIDTH     215
#define SCORE_HEIGHT    60
#define OFFSET_SCORE_X  0
#define OFFSET_SCORE_Y  420
#define POS_SCORE_X     0
#define POS_SCORE_Y     10
#define SCORE_OFFSET    24

class Player 
{
    public:
        // attributs
        int life;
        int score;
        int level;

        int difficulty; 
        /* 0 = hit 1 time 
         * 1 = hit 2 time 
         * 2 = hit 3 time
         * 3 = hit 4 time */
        int current_bonus;
        /*
        1 : catch the energy ball
        2 : fire laser beams */

    
        // methodes
        Player();
        ~Player();
        void next_level();
        void gainLife();
        void gainBonus(int bonus);
        void refresh();
};

#endif