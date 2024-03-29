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
}; 
// Dans rules.h
int can_be_played(struct card card, struct card top_card);
int has_won(player player);
void renderOpponentCards(player *players, int nb_players, int current_player, SDL_Surface *screen);
void renderOpponentCards(player *players, int nb_players, int current_player, SDL_Surface *screen);
void apply_special_card_effect(struct card card, player *players,  int nb_players , int current_player, int *direction, struct card *top_card, SDL_Surface *screen, SDL_Surface *bgImage);
void play_turn(player *players, int nb_players, card *deck, int *deck_size, player *current_player, int *direction, card *top_card, SDL_Surface *screen, SDL_Surface *bgImage);
void renderText(const char *text, int x, int y, SDL_Surface *screen) ;
void calculate_scores();



#endif