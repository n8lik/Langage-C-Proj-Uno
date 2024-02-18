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

int multi ()
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


    //Code pour le jeu
     init_players(players, nb_players);

    // Déclaration et initialisation des variables
    int current_player = 0; // ou choisir un joueur au hasard
    int direction = 1;      // 1 pour sens horaire, -1 pour sens antihoraire
    int nb_cards_to_draw = 0;

    // Déclaration et initialisation de la variable top_card
    card top_card;

    // Création et mélange du deck
    card *deck = create_deck();
    int deck_size = 108;

    display_deck(deck, deck_size);
    shuffle_deck(deck, 108, &top_card);

    //Taille du deck

    distribute_cards(players, deck, nb_players);
    display_cards(players, nb_players);

    // Boucle du jeu
    while (1)
    {
        play_turn(players, nb_players, deck, deck_size, &nb_cards_to_draw, &current_player, &direction, &nb_cards_to_draw, &top_card, screen);

        // Vérifier si le joueur actuel a gagné
        if (has_won(players[current_player]))
        {
            printf("%s a gagné!\n", players[current_player].name);
            break;
        }

        // Passer au joueur suivant
        current_player = (current_player + direction + nb_players) % nb_players;
    }

    // Calculer et enregistrer les scores
    calculate_scores(players, nb_players);

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
