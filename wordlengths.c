#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void histogram(int *x, double *y, int n, int width);
int *histogram_lengths(char **strings, int n);
int find_longest(char **arr_of_str, int len_of_arr);

/*! Basically, what the below does is find the pointer array with the index of elements corresponding to the number of words of a specific length and insert that into the function histogram which prints out the histogram. */

int main(int argc, char **argv){

        int max_words = 56000;
        int max_word_length = 100;

        if (argc != 2){
                fprintf(stderr, "Incorrect format\n");
                return 1;
        }

        FILE *fp;
        char words[max_words][max_word_length];
        int count = 0;

        if ((fp = fopen(argv[1], "r")) == NULL){
                fprintf(stderr, "Cannot open file.\n");
                exit(EXIT_FAILURE);
        }

        while (count < max_words && fscanf(fp, "%s", words[count]) == 1){ /*! This line reads each line of the file fp and stores it in the array words, at the index, count. */
                count++;
        }

        char **words_ptr; /*! Ppinter array with each element pointing to each word in the file fp. */
        words_ptr = (char **)malloc(count * sizeof(char*));
        if (words_ptr  == NULL){
                fprintf(stderr, "Memory allocation failed.\n");
                return 1;
        }
        int l;
        for (l = 0; l < count; l++){
                words_ptr[l] = words[l];
        }

        int sizeofarray = find_longest(words_ptr, count);
        int *drac_histogram_lengths = (int *)malloc((sizeofarray * sizeof(int)));
        if (drac_histogram_lengths == NULL){
                fprintf(stderr, "Memory allocation failed.\n");
                free(words_ptr);
                return 1;
        }
        drac_histogram_lengths = histogram_lengths(words_ptr, count); /*! To return a pointer array with each element corresponding to the number of words with that index of that element. */

        int *index_no = (int *)malloc(count * sizeof(int));
        if (index_no == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                free(words_ptr);
                free(drac_histogram_lengths);
                return 1;
        }

        int k;

        /*! Because the histogram function only takes in a double pointer array, and histogram_lengths only returns a int pointer array, we have to convert the arrays into a suitable data type. */

        double *drac_histogram_lengths_double = (double *)malloc((sizeofarray + 1) * sizeof(double));
        if (drac_histogram_lengths_double == NULL){
                fprintf(stderr, "Memory allocation failed.\n");
                free(words_ptr);
                free(drac_histogram_lengths);
                return 1;
        }
        for (k = 0; k < sizeofarray + 1; k++){
                index_no[k] = k;
                drac_histogram_lengths_double[k] = (double)drac_histogram_lengths[k];
        }

        /*! The function below prints out the histogram which shows the frequency of the words with a specific letter count occuring in the file fp. */

        histogram(index_no, drac_histogram_lengths_double, sizeofarray+1, count/4); /*! The width is count divded by four for ease of visualisation. */

        free(words_ptr);
        free(index_no);
        free(drac_histogram_lengths);
        free(drac_histogram_lengths_double);
        fclose(fp);

        return EXIT_SUCCESS;
}