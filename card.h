#ifndef DEF_HEADER_HASHMAP
#define DEF_HEADER_HASHMAP

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum Color Color;
enum Color{
    YELLOW, RED, BLUE, GREEN, BLACK
};

typedef enum Type Type;

enum Type{
    NORMAL, SPECIAL
};

typedef struct card card;
struct card{
    int value;
    Color color;
    Type type;
};

const char* get_card_name(int value);
const char* get_color_name(Color c);
const char* get_type_name(Type t);
card *create_deck(); 
void shuffle_deck(card *deck, int deck_size);

#endif // DEF_HEADER_HASHMAP
