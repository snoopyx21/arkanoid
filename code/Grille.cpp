#include "Grille.h"

Grille::Grille(SDL_Surface* win, SDL_Surface* sprite): Mobject(win,sprite)
{
    x           = SIDE_WIDTH;
    y           = 80 + UP_HEIGHT;
    height      = win->h - y;
    width       = win->w - 2*x;
    pos         = 0;
    nb_bricks   = 0;
    int i, j;
    for( i = 0 ; i < XMAX ; i++)
    {
        for( j = 0 ; j < YMAX ; j++)
        {
            grid[i][j] = new Brick(win,sprite,i,j);
        }
    }    
}

Grille::~Grille()
{
    int i, j;
    for( i = 0 ; i < XMAX ; i++)
    {
        for( j = 0 ; j < YMAX ; j++)
        {
            delete grid[i][j];
        }
    }  
}


void Grille::update()
{

    for( auto i = 0 ; i < XMAX ; i++)
    {
        for( auto j = 0 ; j < YMAX ; j++)
        {
            grid[i][j]->init(-1,0);
        }
    }
}

void Grille::viewBg()
{
    int i, j;
    SDL_Rect object = { 0,0,0,0 };
    for(j = 80; j < win->h ; j+=srcBg.h)
    {
        for (int i = 0; i < win->w; i += srcBg.w)
        {
            object.x = i;
            object.y = j;
            SDL_BlitSurface(sprite, &srcBg, win, &object);
        }    
    }
}

void Grille::view()
{
    int i, j;
    SDL_Rect object = { 0,0,0,0 };

    this->viewBg();


    for(j = 80 + srcRCorner.h; j < win->h; j+=srcRSide.h)
    {
        object.x = 0;
        object.y = j;
        SDL_BlitSurface(sprite, &srcLSide, win, &object); 
        object.x = win->w - srcRSide.w;
        SDL_BlitSurface(sprite, &srcRSide, win, &object); 
    }

    for(i = srcRCorner.w; i < win->w - srcRCorner.w;i+=srcUp.w)
    {
        object.x = i;
        object.y =  80;
        SDL_BlitSurface(sprite, &srcUp, win, &object); 
        
    }
    object.y= 80;
    object.x=0;
    SDL_BlitSurface(sprite, &srcLCorner, win, &object); 
    object.x=win->w - srcRCorner.w;
    SDL_BlitSurface(sprite, &srcRCorner, win, &object);

    for( i = 0 ; i < XMAX ; i++)
    {
        for( j = 0 ; j < YMAX ; j++)
        {
            /* on peut détruire la brique */
            if (grid[i][j]->life > 0 ||  grid[i][j]->id == 13)
            {
                grid[i][j]->view();
            }
        }
    }
}

//use cin ...
void Grille::next_level(int level, int difficulty)
{
    nb_bricks = 0;
    pos = XMAX*(level-1);
    /* ouverture en lecture */
    std::ifstream fichier("Grille.txt", std::ios::in);
    /* si l'ouverture a fonctionné */
    if (fichier)
    {
        int i;
        int x;
        int y;
        int bid;
            
        i = 0;
        x = 0;
        y = 0;

        std::string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
        while(std::getline(fichier, contenu))  // tant que l'on peut mettre la ligne dans "contenu"
        {
            i++;  // on avance dans le fichier txt
            if (i < pos) 
            {
                /*  si on est pas à la bonne ligne - pos contient la dernière valeur du niveau dans le txt */
                continue;
            }
            if (i >= pos)
            {
                y = 0;
                    
                /* placement */
                std::string token;
                std::istringstream iss(contenu);
                while( std::getline( iss, token, ',' ) )
                {
                    if (y > YMAX) 
                    {
                        break;
                    }
                    bid  = std::stoi(token);
                    if(bid != -1)
                    {
                        if (bid != 13)
                        {
                            nb_bricks++;
                        }
                        grid[x][y]->init(bid, difficulty);
                    }
                    y++;
                }
                x++; // passage ligne suivante de la matrice / grille
            }
            if (x == XMAX) 
            {
                break;
            }
        } /* while */
    }
    else
    {
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
        exit(EXIT_FAILURE);
    }
    fichier.close();
}