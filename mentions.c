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

    //Affichage des mentions légales en un seul bloc
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, "Ce jeu a été réalisé par des étudiants de l'ESGI dans le cadre d'un projet de programmation en C.", textColor);
    SDL_Rect textPosition2;
    textPosition2.x = 40;
    textPosition2.y = 150;
    SDL_BlitSurface(textSurface, NULL, screen, &textPosition2);

    //Affichage des mentions légales en un seul bloc
    SDL_Surface *textSurface2 = TTF_RenderText_Blended(font, "Il n'est pas libre de droit et ne peut être vendu. Il est destiné à un usage personnel.", textColor);
    SDL_Rect textPosition3;
    textPosition3.x = 40;
    textPosition3.y = 200;
    SDL_BlitSurface(textSurface2, NULL, screen, &textPosition3);

    //Affichage des mentions légales en un seul bloc
    SDL_Surface *textSurface3 = TTF_RenderText_Blended(font, "Pour toute question ou réclamation, veuillez contacter l'adresse suivante : 123@gmail.com", textColor);
    SDL_Rect textPosition4;
    textPosition4.x = 40;
    textPosition4.y = 250;
    SDL_BlitSurface(textSurface3, NULL, screen, &textPosition4);
    
    //Faire un bouton qui renvoie au menu position 40 40
    SDL_Surface *textSurface4 = TTF_RenderText_Blended(font, "Retour au menu", textColor);
    SDL_Rect textPosition5;
    textPosition5.x = 40;
    textPosition5.y = 40;
    SDL_BlitSurface(textSurface4, NULL, screen, &textPosition5);
    

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