#include "point.h"

//Option de build dans les linker setting mettre les libSDL2main.a libSDL2.dll.a
//Dans search directory
//Option de build compiler mettre les include
//Option de build linker mettre les lib

//mettre dans build linker -lmingw32


int main(int argc, char *argv[])
{

     game myGame;
     gameState state;

     Brique TabBrique[NB_BRIQUES_X][NB_BRIQUES_Y];

     Joueur Player;

     Balle Ball;

    //Pour les 60 fps
    unsigned int frameLimit = SDL_GetTicks() + 16;


    if(init("Chapter 1 setting up SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame,&Player,&Ball,&TabBrique)){

                state.g_bRunning=1;


    }else{

            return 1;//something's wrong

    }


    while(state.g_bRunning){

           handleEvents(&state,&Player);
           Collision_Balle(&Ball,&Player);
           Move_Raquette(&Player);
           Move_Balle(&Ball,&Player);
           cutBitmapTexture(&myGame,state,&Player,&Ball,&TabBrique);


        // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;
    }

        destroy(&myGame);

        SDL_Quit();

  return 0;
}












