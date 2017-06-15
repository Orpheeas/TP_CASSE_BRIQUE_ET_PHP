#include "point.h"

//Fonctions
//********************************************************************************************************************************************************

int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame,Joueur *Player,Balle *Ball,Brique *TabBrique[NB_BRIQUES_X][NB_BRIQUES_Y]){

    int i,j;

    //Initialize Coordonnees

    //JOUEUR
    Player->Position.x=SCREEN_WIDTH/2-128;
    Player->Position.y=SCREEN_HEIGHT-50;

    //Balle
    Ball->Sprite.x=SCREEN_WIDTH/2-64;
    Ball->Sprite.y=SCREEN_HEIGHT-74;
    Balle_dir_x=none;
    Balle_dir_y=no;

    //Tableau de brique
    for (i=0;i<NB_BRIQUES_Y;i++){
            for (j=0;j<NB_BRIQUES_X;j++){

                TabBrique[i][j]->etat=1;
                TabBrique[i][j]->coord.x=BRIQUE_WIDTH*j;
            }

            TabBrique[i][j]->coord.x=BRIQUE_WIDTH*i;
    }


    //initialize SDL

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_ACCELERATED);


            }


    }else{


        return 0;
    }




    return 1;


}

void handleEvents(gameState *state,Joueur *Player){


    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:Direction_X=gauche  ; break;
                                case SDLK_RIGHT:Direction_X=droite ; break;
                                case SDLK_SPACE:Balle_dir_y=haut ; break;
                            }
                            break;

        case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:Direction_X=immo  ; break;
                                case SDLK_RIGHT:Direction_X=immo; break;
                            }
            ;break;

        default:break;

        }
    }


}

void cutBitmapTexture(game *myGame,gameState state,Joueur *Player,Balle *Ball, Brique *TabBrique[NB_BRIQUES_X][NB_BRIQUES_Y]){

        int i,j;

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;


        //La raquette
        myGame->g_surface = IMG_Load("./assets/paddle.png");//Chargement de l'image png

        if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        if(myGame->g_surface){


                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){

                    rectangleSource.x=0;//128*(int)((SDL_GetTicks()/100)%6);
                    rectangleSource.y=0;
                    rectangleSource.w=128;//1 image = w:128 et h:82
                    rectangleSource.h=32;

                    SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=Player->Position.x;//debut x
                    rectangleDest.y=Player->Position.y;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);

                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }

        //La balle
        myGame->g_surface = IMG_Load("./assets/Ball.png");//Chargement de l'image png

        if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
            // handle error
        }

        if(myGame->g_surface){


                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){

                    rectangleSource.x=0;//128*(int)((SDL_GetTicks()/100)%6);
                    rectangleSource.y=0;
                    rectangleSource.w=24;//1 image = w:128 et h:82
                    rectangleSource.h=24;

                    SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=Ball->Sprite.x;//debut x
                    rectangleDest.y=Ball->Sprite.y;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);

                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }


        /*
        //Les Briques
        for (i=1;i<NB_BRIQUES_Y+1;i++){

            for(j=1;j<NB_BRIQUES_X+1;j++){

                myGame->g_surface = IMG_Load("./assets/Bricks.png");//Chargement de l'image png

                if(!myGame->g_surface) {
                    fprintf(stdout,"IMG_Load: %s\n", IMG_GetError());
                    // handle error
                }

                if(myGame->g_surface){


                    myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                    SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                        if(myGame->g_texture){

                            if ((j%4==1)&&(TabBrique[i][j]->etat==1)){

                                rectangleSource.x=0;
                                rectangleSource.y=0;
                                rectangleSource.w=BRIQUE_WIDTH;
                                rectangleSource.h=BRIQUE_HEIGHT;

                                SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);


                                //Définition du rectangle dest pour dessiner Bitmap
                                rectangleDest.x=j*BRIQUE_WIDTH;//debut x
                                rectangleDest.y=i*BRIQUE_HEIGHT;//debut y
                                rectangleDest.w=rectangleSource.w; //Largeur
                                rectangleDest.h=rectangleSource.h; //Hauteur

                                SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);

                        }else if((j%4==2)&&(TabBrique[i][j]->etat==1)){

                                rectangleSource.x=BRIQUE_WIDTH;
                                rectangleSource.y=0;
                                rectangleSource.w=BRIQUE_WIDTH;
                                rectangleSource.h=BRIQUE_HEIGHT;

                                SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);


                                //Définition du rectangle dest pour dessiner Bitmap
                                rectangleDest.x=j*BRIQUE_WIDTH;//debut x
                                rectangleDest.y=i*BRIQUE_HEIGHT;//debut y
                                rectangleDest.w=rectangleSource.w; //Largeur
                                rectangleDest.h=rectangleSource.h; //Hauteur

                                SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);

                        }else if((j%4==3)&&(TabBrique[i][j]->etat==1)){

                                rectangleSource.x=0;
                                rectangleSource.y=BRIQUE_HEIGHT;
                                rectangleSource.w=BRIQUE_WIDTH;
                                rectangleSource.h=BRIQUE_HEIGHT;

                                SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);


                                //Définition du rectangle dest pour dessiner Bitmap
                                rectangleDest.x=j*BRIQUE_WIDTH;//debut x
                                rectangleDest.y=i*BRIQUE_HEIGHT;//debut y
                                rectangleDest.w=rectangleSource.w; //Largeur
                                rectangleDest.h=rectangleSource.h; //Hauteur

                                SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);

                        }else if((j%4==0)&&(TabBrique[i][j]->etat==1)){

                                rectangleSource.x=BRIQUE_WIDTH;
                                rectangleSource.y=BRIQUE_HEIGHT;
                                rectangleSource.w=BRIQUE_WIDTH;
                                rectangleSource.h=BRIQUE_HEIGHT;

                                SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);


                                //Définition du rectangle dest pour dessiner Bitmap
                                rectangleDest.x=j*BRIQUE_WIDTH;//debut x
                                rectangleDest.y=i*BRIQUE_HEIGHT;//debut y
                                rectangleDest.w=rectangleSource.w; //Largeur
                                rectangleDest.h=rectangleSource.h; //Hauteur

                                SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);

                    }else{
                                fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());

                    }else{
                        fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
                    }

                        }
                }
            }




        }
        */

    SDL_RenderPresent(myGame->g_pRenderer); // Affichage
    SDL_RenderClear(myGame->g_pRenderer);
    destroyTexture(myGame);

}

void delay(unsigned int frameLimit){
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}

void destroy(game *myGame){


    //Destroy render
    if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);


    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}

void destroyTexture(game *myGame){


      //Destroy texture
    if(myGame->g_texture!=NULL)
        SDL_DestroyTexture(myGame->g_texture);


}

void Move_Raquette(Joueur *Player){
//BUT DEPLACER LA RAQUETTE
//ENTREE La structure joueur
//SORTIE La raquette qui a bougé


    if ((Direction_X==gauche)&&(Player->Position.x>10)){
        Player->Position.x-=10;
    }else if((Direction_X==droite)&&(Player->Position.x<SCREEN_WIDTH-138)){

        Player->Position.x+=10;
    }

}

void Move_Balle(Balle *Ball, Joueur *Player){
//BUT Déplacer la balle
//ENTREE Les structures balle et joueur
//SORTIE Le sprite de la balle qui est déplacé


    if ((Balle_dir_x==none)&&(Balle_dir_y==no)){
        Ball->Sprite.x=(Player->Position.x+64);
        Ball->Sprite.y=SCREEN_HEIGHT-74;
    }
    else if ((Balle_dir_x==left)){
        Ball->Sprite.x-=10;
    }

    else if ((Balle_dir_x==right)){
        Ball->Sprite.x+=10;
    }

    if ((Balle_dir_y==haut)){
        Ball->Sprite.y-=10;
    }else if (Balle_dir_y==bas){
        Ball->Sprite.y+=10;
    }

}

void Collision_Balle(Balle *Ball, Joueur *Player){
//BUT Gerer les rebonds de la balle
//ENTREE Les structures balle et joueur
//SORTIE Les enum modifiés en fonction de la position et du mouvement de la balle


    //Collisions avec les murs de cote
    if (((Ball->Sprite.x<=0)&&(Balle_dir_y==haut))){
        Balle_dir_x=right;
        Balle_dir_y=haut;

    }else if((Ball->Sprite.x<=0)&&(Balle_dir_y==bas)){
        Balle_dir_x=right;
        Balle_dir_y=bas;

    }else if((Ball->Sprite.x>=SCREEN_WIDTH)&&(Balle_dir_y==haut)){
        Balle_dir_x=left;
        Balle_dir_y=haut;

    }else if((Ball->Sprite.x>=SCREEN_WIDTH)&&(Balle_dir_y==bas)){
        Balle_dir_x=left;
        Balle_dir_y=bas;
    }


    //Collisions avec le plafond
    if ((Ball->Sprite.y<=0)&&(Balle_dir_x==left)){
        Balle_dir_x=left;
        Balle_dir_y=bas;

    }else if((Ball->Sprite.y<=0)&&(Balle_dir_x==right)){
        Balle_dir_x=right;
        Balle_dir_y=bas;

    }else if ((Ball->Sprite.y<=0)&&(Balle_dir_x==none)){  //Ce test est pour la première collision, on choisis arbitrairement d'envoyer la balle à gauche avec la collision
        Balle_dir_x=left;
        Balle_dir_y=bas;

    }

    //Gestion de la défaite
    if (Ball->Sprite.y+24>=SCREEN_HEIGHT){
       Balle_dir_x=none;
       Balle_dir_y=no;
    }

     //Collisions avec la raquette
    if((Ball->Sprite.x+24>=Player->Position.x)&&(Ball->Sprite.x+24<=Player->Position.x+64)&&(Ball->Sprite.y+24>=Player->Position.y)){

       Balle_dir_x=left;
       Balle_dir_y=haut;
       }else if((Ball->Sprite.x+24<=Player->Position.x+128)&&(Ball->Sprite.x+24>=Player->Position.x+64)&&(Ball->Sprite.y+24>=Player->Position.y)&&(Balle_dir_y==bas)){

       Balle_dir_x=right;
       Balle_dir_y=haut;
       }

    //Gestion des collisions avec les briques
    //WORK IN PROGRESS C'est la hess
}
