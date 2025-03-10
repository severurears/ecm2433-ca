#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//! This function returns a double featuring the largest number in an array with elements of type double. It takes in an array of data type double and the total length of this array

/* How it works: Assuming the first element is the largest number, it compares this number with the next element in the array, and then with the next, so on and so forth.
Once a number larger than the first element is identified, the "biggest" number is now that, and it is compared with the proceeding elements to find an even bigger number.
This process is repeated until the last element has been compared. */

double find_largest(double arr_of_no[], int len_of_arr){
        double biggest = arr_of_no[0];
        int i;
        for (i = 1; i < len_of_arr; i++){
                if (arr_of_no[i] > biggest){
                        biggest = arr_of_no[i];
                }
        }
        return biggest;
}

//! This function returns the longest string in an array of strings.

/*! How it works: It functions very similarly to 'find_largest', except that it compares string lengths instead of doubles. */

int find_longest(char **arr_of_str, int len_of_arr){
        int longest = strlen(arr_of_str[0]);
        int i;
        for (i = 1; i < len_of_arr; i++){
                if (strlen(arr_of_str[i]) > longest){
                        longest = strlen(arr_of_str[i]);
                }
        }
        return longest;
}

//! From the coursework specifications: This function prints a simple histogram of the percentages given in the array y against the numbers in array x.

/*! The parameters int n and int width are the length of the arrays x and y and the maximum number of stars respectively.
How it works: The function works by finding the ratio of stars to percentage, using the ratio of the maximum percentage and largest number of stars as a reference. */

void histogram(int *x, double *y, int n, int width){
        double largest_num = find_largest(y, n);
        double stars_per_percentage = floor(width/largest_num);
        int i;
        for (i = 0; i < n; i++){
                printf("%d ", *(x + i)); /*! This prints the number index on the left. */
                int star_count = (int)(y[i] * stars_per_percentage); /*! This calculates the number of stars per percentage line. */
                int j;
                for (j = 0; j < star_count+1; j++){
                        printf("*"); /*! This prints the stars. */
                }
                printf(" %g\n", y[i]); /*! This prints the percentage in y on the right of the stars. */
        }
}

//! From the coursework specifications: This function takes in an array called strings and its corresponding length, and returns an array of integers, H, where H[i] is the number of times that strings of length i occurred in that array called strings.

/*! How it works: The function initialises an array and alloctes memory to sufficient to accommodate a maximum number of elements equivalent to the longest string.
The main part of the function has two for-loops: (1) the one looping through i loops through every single possible string length and (2) loops through every possible element in the array strings with that string length indicated by i.
The function then returns the number of strings with that particular length in an array. */

int *histogram_lengths(char **strings, int n){
        int longest_strlen = find_longest(strings, n);
        int *length_arrays;
        length_arrays = (int *)malloc((longest_strlen + 1) * sizeof(int));
        if (length_arrays == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                return 1;
        }

        length_arrays[0] = 0;
        int i;
        for (i = 1; i < (longest_strlen + 1); i++){ /*! The function first loops through all possible string lengths. Hence, elements are added into the array in ascending order. */
                int count = 0;
                int j;
                for (j = 0; j < n; j++){ /*! The next for-loop goes through all the elements in the strings array, checking if any match the current i value. */
                        if (strlen(strings[j]) == i){
                                count++; /*! If the i value matches the string length, then it is added to count. */
                        }
                }
                length_arrays[i] = count; /*! The element of the array to-be-returned is changed to the number of strings with the length corresponding to the index of the array. */
        }

        return length_arrays;
}