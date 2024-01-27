#ifndef DEF_HEADER_CARD
#define DEF_HEADER_CARD
#define MAX_CARDS_PER_PLAYER 108
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum Color Color;
enum Color{
    YELLOW, 
    RED, 
    BLUE, 
    GREEN, 
    BLACK
};

typedef enum Type Type;

enum Type{
    NORMAL, 
    deux,
    sens,
    pass,
    joker,
    quatre

};

typedef struct card card;
struct card{
    int value;
    Color color;
    Type type;
    int top_card;
};

const char* get_card_name(int value);
const char* get_color_name(Color c);
const char* get_type_name(Type t);
card *create_deck(); 
void shuffle_deck(card *deck, int deck_size, card *top_card);

#endif 