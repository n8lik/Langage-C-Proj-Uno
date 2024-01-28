#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// sdl 1.2
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "board.h"

int board(int argc, char *argv[])
{
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

    SDL_Surface *bgImage = IMG_Load("backboard.jpg");
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
}