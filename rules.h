#ifndef DEF_HEADER_RULES
#define DEF_HEADER_RULES

#include "card.h"
#include "player.h"
#include <SDL/SDL.h>


typedef struct GameState GameState;

struct GameState{
    card *top_card;   // Carte au sommet de la pile
    int direction;    // Direction du jeu
    int currentPlayerIndex; // Index du joueur actuel
    // ... autres champs nécessaires ...
}; 
// Dans rules.h
int can_be_played(struct card card, struct card top_card);
int has_won(player player);
void apply_special_card_effect(struct card card, struct player *players, int nb_players, int *current_player, int *direction, int *nb_cards_to_draw, struct card *top_card, struct card *deck, int deck_size);

void play_turn(player *players, int nb_players, card *deck, int deck_size, int *nb_cards_drawn, int *current_player, int *direction, int *nb_cards_to_draw, card *top_card, SDL_Surface *screen);

void calculate_scores(player *players, int nb_players);



#endif