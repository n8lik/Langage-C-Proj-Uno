#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mentions.h"
#include "home.h"

//Afficher des mentions légales sans fermer la fenêtre de jeu
void display_mentions(SDL_Surface *screen)
{
    //Chargement de l'image de fond
    SDL_Surface *backgroundImage = IMG_Load("assets/background.jpg");
    if (!backgroundImage)
    {
        fprintf(stderr, "Unable to load background image: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }

    //Affichage de l'image de fond
    SDL_BlitSurface(backgroundImage, NULL, screen, NULL);

    //Chargement de la police
    TTF_Font *font = TTF_OpenFont("assets/DUSTERY.ttf", 25);
    if (!font)
    {
        fprintf(stderr, "Unable to load font: %s\n", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    //Chargement du texte
    SDL_Color textColor = {255, 255, 255,0};
    SDL_Surface *text = TTF_RenderText_Blended(font, "Mentions légales", textColor);
    if (!text)
    {
        fprintf(stderr, "Unable to render text: %s\n", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    //Affichage du texte
    SDL_Rect textPosition;
    textPosition.x = 600;
    textPosition.y = 50;
    SDL_BlitSurface(text, NULL, screen, &textPosition);
    
    //Faire un bouton qui renvoie au menu
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, "Retour au menu", textColor);
    SDL_Rect textPosition2;
    textPosition2.x = 40;
    textPosition2.y = 40;
    SDL_BlitSurface(textSurface, NULL, screen, &textPosition2);

    //Rafraîchissement de l'écran
    SDL_Flip(screen);

    //Voir si on appuie sur le bouton pour retourner au menu rouverture de home_page()
    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        
        //Cas ou on appuie sur le bouton pour retourner au menu
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT && event.button.x >= 40 && event.button.x <= 40 + textSurface->w && event.button.y >= 40 && event.button.y <= 40 + textSurface->h)
            {
                home_page();
            }
            break;
        }
    }


    //Libération de la mémoire
    SDL_FreeSurface(backgroundImage);
    TTF_CloseFont(font);
    SDL_FreeSurface(text);
}
