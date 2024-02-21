#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// sdl 1.2
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "../card.h"
#include "../player.h"
#include "../rules.h"
#include "../home.h"
#include "multi.h"

int multi()
{
    // Initialisation du jeu avec le nombre de joueurs et leurs nomss
    int nb_players = choose_nb_players();
    player *players = malloc(nb_players * sizeof(player));
    choose_players_name(players, nb_players);

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

    // Code pour le jeu
    init_players(players, nb_players);

    // Déclaration et initialisation des variables
    int current_player = 0; // ou choisir un joueur au hasard
    int direction = 1;      // 1 pour sens horaire, -1 pour sens antihoraire

    // Déclaration et initialisation de la variable top_card
    card top_card;

    // Création et mélange du deck
    card *deck = create_deck();
    int deck_size = 108;

    display_deck(deck, deck_size);
    shuffle_deck(deck, 108, &top_card);

    // Taille du deck
    distribute_cards(players, deck, nb_players);
    deck_size -= nb_players * 7; // Subtract the distributed cards
    display_cards(players, nb_players);

    // Boucle du jeu
    while (1)
    {

        play_turn(players, nb_players, deck, &deck_size, &players[current_player], &direction, &top_card, screen, bgImage);
        // Vérifier si le joueur actuel a gagné
        if (has_won(players[current_player]))
        {
            // Afficher le joueur gagnant et terminer le jeu
            printf("Le joueur gagnant est : %s\n", players[current_player].name);

            // Calculer et enregistrer les scores
            calculate_scores();

            // Création de la fenêtre de victoire et affichage du gagnant grace a renderText
            SDL_Surface *winningWindow = SDL_CreateRGBSurface(0, 1280, 720, 32, 0, 0, 0, 0);
            SDL_FillRect(winningWindow, NULL, SDL_MapRGB(winningWindow->format, 255, 0, 0));
            SDL_BlitSurface(winningWindow, NULL, screen, NULL);
            SDL_Flip(screen);
            TTF_Font *font = TTF_OpenFont("assets/DUSTERY.ttf", 25);
            SDL_Color textColor = {255, 255, 255, 0};
            SDL_Surface *text = TTF_RenderText_Blended(font, "Le joueur gagnant est : ", textColor);
            SDL_Rect textPosition;
            textPosition.x = 600;
            textPosition.y = 50;
            SDL_BlitSurface(text, NULL, screen, &textPosition);
            SDL_Surface *textSurface = TTF_RenderText_Blended(font, players[current_player].name, textColor);
            SDL_Rect textPosition2;
            textPosition2.x = 600;
            textPosition2.y = 100;
            SDL_BlitSurface(textSurface, NULL, screen, &textPosition2);
            SDL_Flip(screen);

            // Creation de "refaire une partie" et "retour au menu"
            SDL_Surface *textSurface2 = TTF_RenderText_Blended(font, "Refaire une partie", textColor);
            SDL_Rect textPosition3;
            textPosition3.x = 600;
            textPosition3.y = 200;
            SDL_BlitSurface(textSurface2, NULL, screen, &textPosition3);
            SDL_Flip(screen);

            SDL_Surface *textSurface3 = TTF_RenderText_Blended(font, "Retour au menu", textColor);
            SDL_Rect textPosition4;
            textPosition4.x = 600;
            textPosition4.y = 300;
            SDL_BlitSurface(textSurface3, NULL, screen, &textPosition4);
            SDL_Flip(screen);

            // Gestion des clics
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
                    if (event.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if (event.button.x > 600 && event.button.x < 800 && event.button.y > 200 && event.button.y < 250)
                        {
                            multi();
                        }
                        if (event.button.x > 600 && event.button.x < 800 && event.button.y > 300 && event.button.y < 350)
                        {
                            home_page();
                        }
                    }
                }
            }
            SDL_Delay(5000);
            break;
        }

        // Passer au joueur suivant
        current_player = (current_player + direction + nb_players) % nb_players;
    }

    // Libération de la mémoire
    free(deck);
    for (int i = 0; i < nb_players; i++)
    {
        free(players[i].cards);
    }
    free(players);

    return 0;

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
