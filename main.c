#include <stdio.h>
#include <stdlib.h>

#include "card.h"
#include "player.h"
#include "rules.h"
#include "board.h"
#include "home.h"

int main()
{
    // Initialisation du jeu
    int nb_players = choose_nb_players();
    player *players = malloc(nb_players * sizeof(player));
    choose_players_name(players, nb_players);
    init_players(players, nb_players);

    // Déclaration et initialisation des variables
    int current_player = 0; // ou choisir un joueur au hasard
    int direction = 1;      // 1 pour sens horaire, -1 pour sens antihoraire
    int nb_cards_to_draw = 0;

    // Déclaration et initialisation de la variable top_card
    card top_card;

    // Création et mélange du deck
    card *deck = create_deck();
    shuffle_deck(deck, 108, &top_card);

    // Taille actuelle du deck sans les autres cartes
    int deck_size = 108 - nb_players * 7 - 1;

    distribute_cards(players, deck, nb_players);
    display_cards(players, nb_players);

    // Boucle du jeu
    while (1)
    {
        play_turn(players, nb_players, deck, deck_size, &nb_cards_to_draw, &current_player, &direction, &nb_cards_to_draw, &top_card);

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
}
