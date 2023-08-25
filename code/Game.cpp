#include "Game.h"

Game::Game() 
{
}


Game::~Game() 
{
}


void Game::clean_up()
{
	delete grid;
	delete wtMan;
	delete player;
	delete player1;
	all_bonus.clear();
	all_ball.clear();
	all_vaus.clear();
	SDL_FreeSurface(win_surf);
	SDL_FreeSurface(sprites_surf);
	SDL_DestroyWindow(window);
	SDL_Quit();

}


bool Game::init() 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
		cerr <<"Echec de l'initialisation de la SDL "<<SDL_GetError() << endl;
		return false;
    }

	window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		GAME_WIDTH, GAME_HEIGTH, SDL_WINDOW_SHOWN);
    
	if (!window) {
        cout << "Error creating window:" << SDL_GetError() << endl;
        return false;
    }	

	win_surf = SDL_GetWindowSurface(window);

	sprites_surf = SDL_LoadBMP("./Arkanoid_sprites.bmp");
	SDL_SetColorKey(sprites_surf, true, 0);

	grid = new Grille(win_surf,sprites_surf);

	player = new Player();
	player1 = new Player();

	wtMan = new WriteManager(win_surf,sprites_surf);
	disMenu = 1;
	mode = 0;
	firstLevel = 1;
	bestScore = 0;

    return true;
}


void Game::run() 
{
	int mouseclick = 0;
	bool quit = false;
	int add;
	while (!quit)
	{
		SDL_Event event;
		while (!quit && SDL_PollEvent(&event))
		{
			if(mode)
			{
				disMenu = 0;
				if(firstLevel)
					update(mode);
			}

			switch (event.type)
			{
				case SDL_QUIT:
					quit = true;
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						// touche clavier
						case SDLK_LEFT: 
							if(!mode)
								break;
							if(all_vaus[0]->x >= grid->x + 5)
							{
								all_vaus[0]->x -= 10; 
								if(mode == 2)
									break; 
								for (auto it = all_ball.begin(); it != all_ball.end(); ++it) 
									if((*it)->catched)
										(*it)->x -= 10;
							}
							break;

						case SDLK_RIGHT:
							if(!mode)
								break;
							if(all_vaus[0]->x + all_vaus[0]->width <= grid->x + grid->width - 5)
							{
								all_vaus[0]->x += 10;
								if(mode == 2)
									break; 
								for (auto it = all_ball.begin(); it != all_ball.end(); ++it) 
									if((*it)->catched)
										(*it)->x += 10;
							}

							break;
						case SDLK_m:
							mode = 0;
							disMenu = 1;
							firstLevel = 1;
							break;
						case SDLK_n:
							update(mode);
							break;

						case SDLK_ESCAPE: 
							quit = true; 
							break;
						default: break;
					}
				break;

			case SDL_MOUSEMOTION:	
				if(!mode)
					break;
				Vaus * vaus;
				if(mode == 2)
				{
					vaus = all_vaus[1].get();
				}
				else
					vaus = all_vaus[0].get();
				if(vaus->x  + vaus->width + event.motion.xrel >= grid->x + grid->width)	
					add = (grid->x + grid->width) - (vaus->x  + vaus->width);
				else if(vaus->x + event.motion.xrel <= grid->x)
					add = (grid->x - vaus->x);
				else
					add = event.motion.xrel;
				vaus->x += add;
				for (auto it = all_ball.begin(); it != all_ball.end(); ++it) 
					if((*it)->catched)
						(*it)->x += add;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouseclick = 1;
				break;

			default: break;
			}
		}/* WHILE */

		if(mouseclick && disMenu)
		{
			menu( event.motion.x, event.motion.y, 1);
			firstLevel = 1;
		}
		else if(disMenu)
			menu(0,0,0);
		else
		{
			for (auto it = all_ball.begin(); it != all_ball.end(); ++it)
			{
				if(mouseclick && (*it)->catched)
				{
					(*it)->shot();
				}
			} 
			view();
		}

		SDL_UpdateWindowSurface(window); 
		SDL_Delay(FPS_DELAY); // 50 fps 
		mouseclick = 0;
	}/* WHILE */

}


void Game::update(int mode) 
{//segfault
	switch(mode)
	{
		case 1:
			if(!firstLevel)
			{
				player->next_level();
				player->gainLife();			
			}
			else
				player->refresh();
			grid->update();
			all_ball.clear();
			all_vaus.clear();
			all_bonus.clear();
			all_ball.push_back(shared_ptr<Ball> (new Ball(win_surf,sprites_surf)));

			all_vaus.push_back(shared_ptr<Vaus> (new Vaus(win_surf,sprites_surf)));

			grid->next_level(player->level, player->difficulty);
			all_ball[0]->setDefault();
			all_ball[0]->normalSpeed();
			all_vaus[0]->setDefault();
			all_vaus[0]->normalVaus();
			firstLevel = 0;	
			break;
		case 2:
			if(!firstLevel)
			{
				player->next_level();
				player1->next_level();
				player->gainLife();
				player1->gainLife();
				player1->score = player->score;			
			}
			else
			{
				player->refresh();
				player1->refresh();
			}
			grid->update();
			all_ball.clear();
			all_vaus.clear();
			all_bonus.clear();
			all_ball.push_back(shared_ptr<Ball> (new Ball(win_surf,sprites_surf)));

			all_vaus.push_back(shared_ptr<Vaus> (new Vaus(win_surf,sprites_surf)));
			all_vaus.push_back(shared_ptr<Vaus> (new Vaus(win_surf,sprites_surf)));

			grid->next_level(player->level, player->difficulty);
			all_vaus[0]->setDefault();
			all_vaus[0]->normalVaus();
			all_ball[0]->setDefault();
			all_ball[0]->normalSpeed();
			all_vaus[1]->setDefault();
			all_vaus[1]->normalVaus();
			all_vaus[1]->y = all_vaus[0]->y - all_vaus[1]->height - 3;
			all_ball[0]->y = all_vaus[1]->y - all_ball[0]->height - 1;
			firstLevel = 0;				
		default:
			break;	
	}
}


void Game::menu(int x, int y, int click)
{
	int i,j;
	if(click)
	{
		if((x >= 215 && x <=215 + 4*32) && (y >= 128 && y <=128 + 32)) 
			mode = 1;
		else if((x >= 210 && x <=210 + 5*32) && (y >= 196 && y <=196 + 32))
			mode = 2;
		else if((x >= 210 && x <=210 + 5*32) && (y >= 256 && y <=256 + 32))
			mode = 0;
		else if((x >= 210 && x <=210 + 5*32) && (y >= 312 && y <=312 + 32))
			mode = 0;
		else 
			mode = 0;

	}
    srcLogo.x = 320;
    srcLogo.y = 190;
	srcLogo.w = 64;
    srcLogo.h = 64;

    resLogo.x = 0;
    resLogo.y = 0;
	resLogo.w = 64;
    resLogo.h = 64;
    for(j = 0; j < 80 ; j+=64)
    {
        for (i = 0; i < win_surf->w; i += 64)
        {
            resLogo.x = i;
            resLogo.y = j;
            SDL_BlitSurface(sprites_surf, &srcLogo, win_surf, &resLogo);
        }    
    }
    srcLogo.x = OFFSET_SCORE_X;
    srcLogo.y = OFFSET_SCORE_Y;
	srcLogo.w = SCORE_WIDTH;
    srcLogo.h = SCORE_HEIGHT;

    resLogo.x = 140;
    resLogo.y = 396;
	resLogo.w = 321;
    resLogo.h = 90;

	grid->viewBg();
	string label0("Start Arkanoid");
	string label01("Choose a Mode");
	string label1("SOLO");
	string label2("CO-OP");
	string label3("ToAdd");
	string label4("ToAdd");
	string label5("Best Score :");

	wtMan->writeOnSurf(label0,132,5);
	wtMan->writeOnSurf(label01,142,32);
	wtMan->writeOnSurf(label1,215,128);
	wtMan->writeOnSurf(label2,215,196);
	wtMan->writeOnSurf(label3,210,256);
	wtMan->writeOnSurf(label4,210,312);

	SDL_BlitSurface(sprites_surf, &srcLogo, win_surf, &resLogo);
	wtMan->writeOnSurf(label5,120,500);
	wtMan->writeOnSurf(to_string(bestScore),120 + 16*12,500);
}


void Game::view() 
{
	int i, j;

	if((mode == 1 && player->life == 0) 
	|| (mode == 2 && player->life == 0 && player1->life == 0) )
	{
		mode = 0;
		disMenu = 1;
		if(player->score > bestScore)
			bestScore = player->score;
		return;
	}

	if(mode == 2)
	{

	}
    srcLogo.x = 320;
    srcLogo.y = 190;
	srcLogo.w = 64;
    srcLogo.h = 64;

    resLogo.x = 0;
    resLogo.y = 0;
	resLogo.w = 64;
    resLogo.h = 64;
    for(j = 0; j < 80 ; j+=64)
    {
        for (i = 0; i < win_surf->w; i += 64)
        {
            resLogo.x = i;
            resLogo.y = j;
            SDL_BlitSurface(sprites_surf, &srcLogo, win_surf, &resLogo);
        }    
    }

/*********************** SCORE ************************************/
    string label("SCORE:");

    wtMan->writeOnSurf(label,SCORE_WIDTH,SCORE_OFFSET);

	/* affichage score */
	string tmp_score = to_string(player->score);

    wtMan->writeOnSurf(tmp_score,SCORE_WIDTH + LETTER_W*4,SCORE_OFFSET);
/*********************** SCORE ************************************/

    srcLogo.x = OFFSET_SCORE_X;
    srcLogo.y = OFFSET_SCORE_Y;
	srcLogo.w = SCORE_WIDTH;
    srcLogo.h = SCORE_HEIGHT;

    resLogo.x = POS_SCORE_X;
    resLogo.y = POS_SCORE_Y;
	resLogo.w = SCORE_WIDTH;
    resLogo.h = SCORE_HEIGHT;

    SDL_BlitSurface(sprites_surf, &srcLogo, win_surf, &resLogo);

	grid->view();

	for (auto it = all_ball.begin(); it != all_ball.end(); ++it) 
	{
		(*it)->view();
	}

	for ( auto i = all_vaus.begin(); i != all_vaus.end(); ++i)
	{
		(*i)->view();
	}	

	for ( auto i = all_bonus.begin(); i != all_bonus.end(); ++i)
	{
		(*i)->view();
	}	

    int life = player->life;
    if(mode == 2)
    	life += player1->life;
    srcLogo.x = 400;
    srcLogo.y = 112;
	srcLogo.w = 3;
    srcLogo.h = 13;

	resLogo.x = 30;
    resLogo.y = GAME_HEIGTH - 15;
	resLogo.w = 3;
    resLogo.h = 13;
    for(auto i = 0; i < life; i++)
    {
    	SDL_BlitSurface(sprites_surf, &srcLogo, win_surf, &resLogo);
    	resLogo.x += 5;
    }

	vausCollisions();
	brickCollisions();
	bonusCollisions();
	boardCollisions();
	for (auto it = all_ball.begin(); it != all_ball.end(); ++it) 
	{
		(*it)->setDirection();
	}
	if(grid->nb_bricks == 0)
	{
		update(mode);
	}
}


void Game::boardCollisions() 
{
	int nErased; // not erased
	for (auto it = all_ball.begin(); it != all_ball.end();) 
	{
		nErased = 1;
		// collision bord
		if (((*it)->x <= grid->x) || ((*it)->x >= (grid->x + grid->width - (*it)->width)))
		{
			(*it)->dirx *= -1;
		}
		else if (((*it)->y <= grid->y))
		{
			(*it)->diry *= -1;
		}
		else if ((*it)->y >(win_surf->h - (*it)->height))
		{
			if(all_ball.size() > 1)
			{
				it = all_ball.erase(it);
				nErased = 0;
			}
			else
			{
				Vaus * vaus;
				if(mode == 1)
				{
					vaus = all_vaus[0].get();
					player->life--;
				}
				if(mode == 2)
				{
					vaus = all_vaus[1].get();
					if(player->life == 0)
					{
						player1->life--;
					}
					else
						player->life--;
				}
				all_ball[0]->setDefault();
				all_ball[0]->normalSpeed();
				all_ball[0]->x = vaus->x;
				all_ball[0]->y = vaus->y - vaus->height - 1;			
			}
		}

		if(nErased)
			++it;

	}
}


void Game::vausCollisions() 
{
	float hit;
	for(auto vaus = all_vaus.begin(); vaus != all_vaus.end(); ++vaus)
	{
		for (auto it = all_ball.begin(); it != all_ball.end(); ++it) 
		{
			if(((*vaus)->collision((*it).get())))// && ((*it)->y + (*it)->height > (*vaus)->y))
			{
				if((*it)->catched)
				{
					return;
				}
				hit = ((*it)->x + (*it)->width/2)-(*vaus)->x;
				if(hit < 0)
					hit = 0;
				else if(hit >(*vaus)->width)
					hit = (*vaus)->width;
				(*it)->dirx = 2 * ((hit-((*vaus)->width/2)) / ((*vaus)->width / 2));
				(*it)->diry *= -1;
				if(player->current_bonus == 1)
				{
					(*it)->ballCatch();
					(*it)->y = (*vaus)->y - (*it)->height -1;
				}
			}
		}
	}
}


void Game::brickCollisions() 
{
   	int i, j, r, hit = 0;
	for (auto it = all_ball.begin(); it != all_ball.end(); ++it) 
	{
	    for( i = 0 ; i < XMAX ; i++)
	    {
	        for( j = 0 ; j < YMAX ; j++)
	        {
            // on peut détruicre la brique 
	            if (grid->grid[i][j]->life != 0 )
	            {
					if( ( (*it)->collision(grid->grid[i][j]) ))
					{
						hit = 1;
						
						grid->grid[i][j]->life--;

						if(grid->grid[i][j]->id == 12 || grid->grid[i][j]->id == 13)
							grid->grid[i][j]->touched = 1;
						/* si la brique est detruite */
						if ( grid->grid[i][j]->life == 0) 
						{
							grid->nb_bricks--;
							player->score += grid->grid[i][j]->score;
							
							if(mode == 1)
							{	
								/* application du bonus */
								r = (rand() % RANDOM_NUMBER);
								if ((r == 0)||(r == 1)||(r == 2)||(r == 3)||(r == 4)||(r == 5)||(r == 6) )
								{
									all_bonus.push_back(shared_ptr<Bonus> (new Bonus(win_surf,sprites_surf,  grid->grid[i][j]->x,  grid->grid[i][j]->y)));
									all_bonus[all_bonus.size()-1]->init(r);
									all_bonus[all_bonus.size()-1]->update();
								}
							}
						}

						/* collision coin d'une brique */
						if (  ( ((*it)->x + ((*it)->width)  > grid->grid[i][j]->x) 
							 && ((*it)->x + ((*it)->width)  < (grid->grid[i][j]->x + grid->grid[i][j]->width/6))
							&&(	((*it)->y + ((*it)->height) > grid->grid[i][j]->y)
							 && ((*it)->y + ((*it)->height) < (grid->grid[i][j]->y + grid->grid[i][j]->height/6))
							 || ((*it)->y > grid->grid[i][j]->y + grid->grid[i][j]->height/6)
							 && ((*it)->y  < (grid->grid[i][j]->y + grid->grid[i][j]->height))
							  ))
							||
							  ( ((*it)->x   > grid->grid[i][j]->x + grid->grid[i][j]->width/6) 
							 && ((*it)->x   < (grid->grid[i][j]->x + grid->grid[i][j]->width))
							&&(	((*it)->y + ((*it)->height) > grid->grid[i][j]->y)
							 && ((*it)->y + ((*it)->height) < (grid->grid[i][j]->y + grid->grid[i][j]->height/6))
							 || ((*it)->y > grid->grid[i][j]->y + grid->grid[i][j]->height/6)
							 && ((*it)->y  < (grid->grid[i][j]->y + grid->grid[i][j]->height))
							  ))
						)

						{
							(*it)->diry *= -1;
							(*it)->dirx *= -1;
						}
						/* collision horizontale */
						else if (((*it)->x + ((*it)->width/2) > grid->grid[i][j]->x) 
							&& ((*it)->x + ((*it)->width/2) < (grid->grid[i][j]->x + grid->grid[i][j]->width)))
						{
							(*it)->diry *= -1;
						}
						/* collision verticale */
						else
						{
							(*it)->dirx *= -1;
						}				
					}
				}
		 		if (hit == 1)
		 		{
		 			break;
		 		}
			}
	 		if (hit == 1)
	 		{
	 			break;
	 		}
 		}
	}
}


void Game::bonusCollisions()
{
	if(mode != 1)
		return;	
	for (auto it = all_bonus.begin(); it != all_bonus.end(); ) 
	{
	    if ((*it)->collision(all_vaus[0].get()))
	    {
	    	bonusEffect((*it)->id);
			it = all_bonus.erase(it);
	    }
		else if((*it)->y > GAME_HEIGTH)
		{
			it = all_bonus.erase(it);			
		} 
	    else 
			++it;
	}
}


void Game::bonusEffect(int bonus_number)
{
	/* https://strategywiki.org/wiki/Arkanoid/Getting_Started */
	player->score += 1000;
	switch(bonus_number)
	{
		/* S: slow down the energy ball */
		case 0 :
			player->gainBonus(-1);
			for (auto it = all_ball.begin(); it != all_ball.end(); ++it) 
			{
				(*it)->reduceSpeed();
			}
			break;
		/* C: catch the energy ball and shoot it back */
		case 1 :
			player->gainBonus(bonus_number);
			break;
		/* L: enables the VAUS to fire laser beams */
		case 2 :
			player->gainBonus(bonus_number);
			break;
		/* E: expands the length of the VAUS craft */
		case 3 :
			player->gainBonus(-1);
			all_vaus[0]->upgradeVaus();
			break;
		/* D: splits the energy ball into three particles */
		case 4 :
			player->gainBonus(-1);
			all_ball.push_back(shared_ptr<Ball> (new Ball(win_surf,sprites_surf)));
			all_ball[all_ball.size()-1]->setCoor(all_ball[0]->x, all_ball[0]->y);
			all_ball[all_ball.size()-1]->dirx *= -1;
			all_ball.push_back(shared_ptr<Ball> (new Ball(win_surf,sprites_surf)));
			all_ball[all_ball.size()-1]->setCoor(all_ball[0]->x, all_ball[0]->y);
			all_ball[all_ball.size()-1]->diry *= -1;
			break;
		/* B: allows the player to warp into the next play-field */
		case 5 :
			player->gainBonus(-1);
			player->score += 10000;
			update(mode);
			break;
		/* P: an additionnal VAUS awarded */
		case 6 :
			player->gainBonus(-1);
			player->gainLife();
			break;
		default:
			break;
	}
}
