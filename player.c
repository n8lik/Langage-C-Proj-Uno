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
        players[i].nbCards = 0;
        players[i].cards = malloc(MAX_CARDS_PER_PLAYER * sizeof(card)); 
    }
}
//ceci est un test
// distribution des cartes
void distribute_cards(player *players, card *deck, int nb_players)
{
    for (int i = 0; i < nb_players; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            players[i].cards[j] = deck[i * 7 + j];
            players[i].nbCards++;
        }
    }
}
// affichage des cartes
void display_cards(player *players, int nb_players)
{
    for (int i = 0; i < nb_players; i++)
    {
        printf("Joueur %d : %s\n", i + 1, players[i].name);
        for (int j = 0; j < players[i].nbCards; j++)
        {
            printf("Carte %d : Valeur=%s, Couleur=%s, Type=%s\n", j + 1, get_card_name(players[i].cards[j].value), get_color_name(players[i].cards[j].color), get_type_name(players[i].cards[j].type));
        }

        printf("Joueur %d a %d cartes après distribution.\n", i + 1, players[i].nbCards);
    }
}
// piocher une carte non déjà distribuée en rajoutant celle qu'on vient de piocher dans les déjà distribuées
card draw_card(card *deck, int *nb_cards_drawn) {
    printf("Avant la pioche: nb_cards_drawn = %d\n", *nb_cards_drawn);

    if (*nb_cards_drawn >= 108) {
        printf("Plus de cartes à piocher\n");
        card no_card;
        no_card.value = -1;
        no_card.color = -1;
        no_card.type = -1;
        return no_card;
    } else {
        card card_drawn = deck[*nb_cards_drawn];
        
        // Décaler toutes les cartes suivantes d'une position vers l'avant
        for (int i = *nb_cards_drawn; i < 107; i++) {
            deck[i] = deck[i + 1];
        }

        // Réduire le nombre total de cartes dans le deck
        (*nb_cards_drawn)++;

        printf("Après la pioche: nb_cards_drawn = %d\n", *nb_cards_drawn);

        return card_drawn;
    }
}
