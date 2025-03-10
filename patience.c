#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

/*! The function add_to_11 below checks the visible cards to see if there are two cards that add to 11, if there are, it alters the return_array to contain the index of those two cards. It takes in an array called visible, the card count (the number of cards in the pile) and an array to fit in the index of where the two cards that add to 11 are. 
*
How it works: loops through the visible array twice, looking for two cards that add to 11. No need to account for j, q, or k because they are greater or equal to 11 by themselves, and there is no 0 card. There is also no need to account for 2 cards of the same number adding to 11 because it is not possible. */

void add_to_11(int visible[], int card_count, int return_array[]){
        int i;
        int j;
        bool found = false;
        for(i = 0; i < card_count; i++){
                for(j = 0; j < card_count; j++){
                        if(visible[i] + visible[j] == 11 && visible[i] != 11 && visible[j] != 11){
                                return_array[0] = i;
                                return_array[1] = j;
                                found = true;
                        }
                }
        }
        if(found == false){
                return_array[0] = -1;
                return_array[1] = -1;
        }
}

/*! The function jqk below checks if the cards j, q and k are present in the visible cards, if they are, it returns a boolean true. It takes in an array called visible and the card count, similar to add_to_11.
*
How it works: It is simple, it just checks for every card, ensuring each are present before true is returned. */

bool jqk(int visible[], int card_count){
        bool foundj = false;
        bool foundq = false;
        bool foundk = false;

        int i;
        for(i = 0; i < card_count; i++){
                if(visible[i] == 11){
                        foundj = true;
                }else if(visible[i] == 12){
                        foundq = true;
                }else if(visible[i] == 13){
                        foundk = true;
                }
        }

        if(foundj && foundq && foundk){
                return true;
        }else{
                return false;
        }
}

/*! The function play below simulates one game. */

int play(int deck[], int verbose){
        int visible[9] = {0}; /* The visible array holds up to 9 cards, cards which are not yet visible are 0. */
        int card_count = 0;
        int deck_index = 0;
        bool won_game = true; /* The game is always won, unless certain conditions are met (remaining cards in the deck where no cards can be added and no cards can be replaced). */

        while(deck_index < 52){

                /* We will first test for whether there are j, q or k in the visible cards. */

                if(jqk(visible, card_count)){
                        int i;

                        /*! The below booleans are to account for multiple j, q, or k in the visible cards. */

                        bool foundj = false;
                        bool foundq = false;
                        bool foundk = false;
                        for(i = 0; i < card_count; i++){
                                if(visible[i] == 11 && foundj == false){
                                        deck_index++;
                                        visible[i] = deck[deck_index];
                                        foundj = true;
                                }else if(visible[i] == 12 && foundq == false){
                                        deck_index++;
                                        visible[i] = deck[deck_index];
                                        foundq = true;
                                }else if(visible[i] == 13 && foundk == false){
                                        deck_index++;
                                        visible[i] = deck[deck_index];
                                        foundk = true;
                                }
                        }

                /* If there are none, then test for whether there are cards that add to 11 visible. */

                }else{
                        int pair_11[2]; /*! Initialise the array that contains the index of the cards that add to 11. */
                        add_to_11(visible, card_count, pair_11);
                        if(pair_11[0] != -1){ /*! If there are pairs that add to 11. */
                                visible[0] = deck[deck_index]; /* Take card from deck. */
                                deck_index++; /*! By incrementing deck_index, we are essentially cycling through the cards on the deck by cycling through the index of these cards. */
                                visible[1] = deck[deck_index];
                                deck_index++;
                        }else{ /*! If no pairs. */
                                if(card_count < 9){ /*! If there are less than 9 cards, this means an additional card can be drawn. */
                                        visible[card_count++] = deck[deck_index];
                                        deck_index++;
                                }else{ /*! Else, if there are 9 or more cards, this means the game cannot be won. */
                                        won_game = false;
                                        if(verbose){ /*! Print the final line of the game if verbose is 1. */
                                                int i;
                                                for(i = 0; i < card_count; i++){
                                                        printf("%d", visible[i])
                                                }
                                        }
                                        break; /*! Break the while loop. */
                                }
                        }
                }

                if(verbose){ /*! Print if verbose is 1. */
                        int i;
                        for(i = 0; i < card_count; i++){
                                printf("%d ", visible[i]);
                        }
                }
        }

        if(won_game && verbose){
                printf("Game won, no more cards in deck.\n");
        }else if(verbose){
                printf("Game lost, no more possible moves with cards still unplayed in deck.\n");
        }

        int cards_left = 52 - deck_index; /*! Find the cards left. */
        return cards_left;
}

/*! Shuffle function taken from ELE. */
        
gsl_rng *shuffle(int *x, int n, int seed)
{
    const gsl_rng_type *T;
    static gsl_rng *r = NULL;

    if (r == NULL) {
        gsl_rng_env_setup();
        if (seed < 0)
            seed = time(NULL);
        gsl_rng_default_seed = seed;

        T = gsl_rng_default;
        r = gsl_rng_alloc (T);
    }

    gsl_ran_shuffle(r, x, n, sizeof(int));
    return r;
}

void free_shuffle(gsl_rng *r)
{
     free(r->state);
     free(r);
     return;
}

/*! This function simulates N plays of the game and returns .*/
        
int *many_plays(int *deck, int N){
        int *remaining = (int *)malloc((N + 1) * sizeof(int));
        if(remaining == NULL){
                fprintf(stderr, "Memory allocation failed.\n");
                return 1;
        }

        int i;
        gsl_rng *r;
        for(i = 0; i < N + 1; i++){
                shuffle(deck, 52, -1);
                int result = play(deck, 0);
                remaining[result]++;
                free_shuffle(r);
        }
        return remaining;
}
        