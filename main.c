#include <stdio.h>
#include <stdlib.h>

#include "card.h"

int main() {
    card *deck = create_deck();
    shuffle_deck(deck, 108);

    // Affichage des cartes pour tester
    for (int i = 0; i < 108; i++) {
        printf("Carte %d: Valeur=%s, Couleur=%s, Type=%s\n", i+1, get_card_name(deck[i].value), get_color_name(deck[i].color), get_type_name(deck[i].type));
    }

    free(deck); // N'oubliez pas de libérer la mémoire
    return 0;
}
