#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"
#include "player.h"

// choix du nombre de joueurs (2 a 4 )
int choose_nb_players()
{
    int nb_players;
    printf("Combien de joueurs ? (2 a 4) ");
    scanf("%d", &nb_players);
    while (nb_players < 2 || nb_players > 4)
    {
        printf("Erreur, veuillez choisir un nombre de joueurs entre 2 et 4 : ");
        scanf("%d", &nb_players);
    }
    return nb_players;
}
// choix du nom des joueurs
void choose_players_name(player *players, int nb_players)
{
    for (int i = 0; i < nb_players; i++)
    {
        printf("Joueur %d, quel est votre nom ? ", i + 1);
        scanf("%s", players[i].name);
    }
}
// initialisation des joueurs
void init_players(player *players, int nb_players)
{
    for (int i = 0; i < nb_players; i++)
    {
        players[i].nb_cards = 0;
        players[i].cards = malloc(7 * sizeof(card));
    }
}
// distribution des cartes
void distribute_cards(player *players, card *deck, int nb_players)
{
    for (int i = 0; i < nb_players; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            players[i].cards[j] = deck[i * 7 + j];
            players[i].nb_cards++;
        }
    }
}
// affichage des cartes
void display_cards(player *players, int nb_players)
{
    for (int i = 0; i < nb_players; i++)
    {
        printf("Joueur %d : %s\n", i + 1, players[i].name);
        for (int j = 0; j < players[i].nb_cards; j++)
        {
            printf("Carte %d : Valeur=%s, Couleur=%s, Type=%s\n", j + 1, get_card_name(players[i].cards[j].value), get_color_name(players[i].cards[j].color), get_type_name(players[i].cards[j].type));
        }
    }
}


int main() {
    // Choix du nombre de joueurs
    int nb_players = choose_nb_players();

    // Création et initialisation des joueurs
    player *players = malloc(nb_players * sizeof(player));
    choose_players_name(players, nb_players);
    init_players(players, nb_players);

    // Création et mélange du jeu de cartes
    card *deck = create_deck();
    shuffle_deck(deck, 108);

    // Distribution des cartes
    distribute_cards(players, deck, nb_players);

    // Affichage des cartes de chaque joueur
    display_cards(players, nb_players);

    // Libération de la mémoire
    for (int i = 0; i < nb_players; i++) {
        free(players[i].cards);
    }
    free(players);
    free(deck);

    return 0;
}
