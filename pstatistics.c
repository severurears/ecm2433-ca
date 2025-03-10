#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

void histogram(int *x, double *y, int n, int width);
int *many_plays(int *deck, int N);
void shuffle(int *x, int n, int seed);
int play(int deck[], int verbose);

int main(){
        int deck[52] = {10, 4, 9, 8, 5, 1, 2, 12, 9, 11, 2, 12, 1, 3, 12, 10, 6, 13, 7, 6, 10, 4, 7, 5, 8, 2, 4, 1, 3, 9, 5, 4, 6, 9, 11, 10, 13, 11, 11, 1, 12, 3, 13, 2, 5, 13, 7, 3, 7, 6, 8, 8};

        /*! Create list to print histogram with. */

        int *hist_list = many_plays(deck, 10000);

        int index[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52};

        FILE *fp = fopen("phistogram.txt", "w"); /*! To print. */
        if(fp == NULL){
                fprintf(stderr, "Cannot open file.\n");
                exit(EXIT_FAILURE);
        }

        freopen("phistogram.txt", "w", stdout);
        histogram(index, (double *)hist_list, 53, 1000); /*! To print histogram in phistogram.txt */
        fclose(fp);

        return 0;
}
