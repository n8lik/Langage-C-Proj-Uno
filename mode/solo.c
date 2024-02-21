#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 

// sdl 1.2
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "../card.h"
#include "../player.h"
#include "../rules.h"
#include "solo.h"

int solo ()
{
    
    // Choix du nombre de joueurs, y compris les IA
    int nb_players = choose_nb_players();
    player *players = malloc(nb_players * sizeof(player));
    
    // Initialisation du joueur humain
    choose_players_name(players, 1); // Peut-être ajuster pour demander seulement le nom du joueur humain
    players[0].isAI = false; // Le premier joueur n'est pas une IA
    
    // Configuration des joueurs IA
    for (int i = 1; i < nb_players; i++) {
        players[i].isAI = true; // Marquer comme IA
    }


    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    int imgFlags = IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL_image : %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *screen = SDL_SetVideoMode(1280, 720, 32, SDL_SWSURFACE);
    if (screen == NULL)
    {
        fprintf(stderr, "Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface *bgImage = IMG_Load("assets/backboard.jpg");
    if (bgImage == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement de l'image : %s\n", IMG_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_BlitSurface(bgImage, NULL, screen, NULL);
    SDL_Flip(screen);

    SDL_Event event;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }
    }

    SDL_FreeSurface(bgImage);
    IMG_Quit();
    SDL_Quit();
    return 0;
}


