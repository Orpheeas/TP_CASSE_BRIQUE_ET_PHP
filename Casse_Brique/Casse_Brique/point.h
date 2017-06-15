#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

//Bibliothèque
//********************************************************************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>


//Constantes
//********************************************************************************************************************************************************

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780
#define NB_BRIQUES 64
#define NB_BRIQUES_X 16
#define NB_BRIQUES_Y 4
#define BRIQUE_WIDTH 64
#define BRIQUE_HEIGHT 24



//Structures
//********************************************************************************************************************************************************

enum Direction_X{

    immo,gauche,droite

}Direction_X;

enum Balle_dir_x{

    none,left,right

}Balle_dir_x;

enum Balle_dir_y{

    no,haut,bas

}Balle_dir_y;

typedef struct game{


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_texture;
     SDL_Surface *g_surface;


}game;

typedef struct gameState{

    int g_bRunning;


}gameState;

typedef struct coordonnees{

    double x;
    double y;



}coordonnees;

typedef struct Brique{

    coordonnees coord;
    int etat;          //Si il vaut 0 la brique est détruite sinon elle vaut 1


}Brique;

typedef struct Joueur{

    SDL_Rect Position;

}Joueur;

typedef struct Balle{

    SDL_Rect Sprite;

}Balle;

//Prototypes
//******************************************************************************************************************************************************
int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame,Joueur *Player,Balle *Ball,Brique *TabBrique[NB_BRIQUES_X][NB_BRIQUES_Y]);
void Collision_Balle(Balle *Ball, Joueur *Player);
void handleEvents(gameState *state,Joueur *Player);
void Move_Raquette(Joueur *Player);
void Move_Balle(Balle *Ball, Joueur *Player);
void delay(unsigned int frameLimit);
void cutBitmapTexture(game *myGame,gameState state, Joueur *Player,Balle *Ball,Brique *TabBrique[NB_BRIQUES_X][NB_BRIQUES_Y]);
void destroyTexture(game *myGame);
void destroy(game *myGame);

#endif // POINT_H_INCLUDED
