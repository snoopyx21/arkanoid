#ifndef GRILLE_H_
#define GRILLE_H_

#include <SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Brick.h"
#include "Mobject.h"

#define XMAX 			25
#define YMAX 			13

#define SIDE_X			494
#define SIDE_R_Y		112
#define SIDE_L_Y		257
#define SIDE_HEIGHT 	94
#define SIDE_WIDTH  	18

#define UP_X			0
#define UP_Y	    	109
#define UP_HEIGHT 		18
#define UP_WIDTH  		218

#define CORNER_L_X		192
#define CORNER_L_Y		0
#define CORNER_L_HEIGHT 40
#define CORNER_L_WIDTH  28

#define CORNER_R_X		220
#define CORNER_R_Y		0
#define CORNER_R_HEIGHT 40	
#define CORNER_R_WIDTH  28



class Grille: public Mobject
{

public :
	// attributs

    SDL_Rect srcBg = {0,128, 48,64 }; // x,y, w,h (0,0) en haut a gauche
    SDL_Rect srcRSide = {SIDE_X ,SIDE_R_Y , SIDE_WIDTH, SIDE_HEIGHT};
    SDL_Rect srcLSide = {SIDE_X ,SIDE_L_Y , SIDE_WIDTH, SIDE_HEIGHT};

    SDL_Rect srcUp = {UP_X ,UP_Y , UP_WIDTH, UP_HEIGHT};
    SDL_Rect srcLCorner = {CORNER_L_X, CORNER_L_Y, CORNER_L_WIDTH, CORNER_L_HEIGHT};
    SDL_Rect srcRCorner = {CORNER_R_X, CORNER_R_Y, CORNER_R_WIDTH, CORNER_R_HEIGHT};

	Brick *grid[XMAX][YMAX]; // grille Arkanoid 13*25 -> parsage fichier stdout.txt
	int pos; // pos/25 +1 = lvl
	int nb_bricks;

	// methodes
	Grille(SDL_Surface* win, SDL_Surface* sprite);
	~Grille();

	void update(); 
	void next_level(int level, int difficulty); // passage au niveau suivant
	void viewBg();
	void view(); // affichage des briques
};

#endif