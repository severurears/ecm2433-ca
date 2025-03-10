#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct wordNode {
    char *word;
    struct wordNode *nextNode;
} WNODE;

typedef struct keyNode {
    char *key;
    WNODE *words;
    struct keyNode *nextNode;
} KNODE;

/*! I will create the following functions to create the corresponding word and key nodes to make it easier and create cleaner code. */

WNODE *create_wnode(char *word){
    WNODE *newnode = (WNODE *)malloc(sizeof(WNODE));
    if (newnode == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    newnode->word = word;
    newnode->nextNode = 1;
    return newnode;
}

KNODE *create_knode(char *key){
    KNODE *newnode = (KNODE *)malloc(sizeof(KNODE));
    if (newnode == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    newnode->key = strdup(key);
    newnode->words = NULL;
    newnode->nextNode = NULL;
    return newnode;
}

/*! This function below just sorts the letters in the word passed in alphabetical order. It simply makes the code cleaner and easier to write.

How it works: It takes in a word and for every single letter in the word, it swaps adjacent letters if the next letter is larger than the current selected letter i. It carries out swaps until no more swpas are required. */

void sortalpha(char *word){
    int length = strlen(word);
    int i;
    for (i = 0; i < length - 1; i++){
        int j;
        for (j = i + 1; j < length; j++){
            if (word[i] > word[j]){
                char temp = word[i];
                word[i] = word[j];
                word[j] = temp;
            }
        }
    }
}

KNODE *make_anagram_list(char **words, int n){
    KNODE *root = NULL;

    int i;
    for (i = 0; i < n; i++){

        /*! Sort the current word to get key. */

        char *key = words[i];
        sortalpha(key);

        KNODE *current = root; /*! Set the current node selection to the root of the linked list. */
        KNODE *prev = NULL;

        /*! This while-loop traverses the nodes in the sorted linked list to ensure that the nodes are in order alphabetically.

        Hence, it continues while current is not NULL and the word in the current node is lexicographically less than the previous key in the previous node. Note that since current = root = NULL, the while loop does not execute for the first node. */

        while (current && strcmp(current->key, key) < 0){
            prev = current;
            current = current->nextNode;
        }

        /*! To account for the first key node in the linked list or where the current key is lexicographically bigger than the previous key (aka when the perfect placement in the linked array for the new key node is found), this code below creates new key node. */

        if (current == NULL || strcmp(current->key, key) > 0){
            KNODE *new_knode = create_knode(key);
            WNODE *new_wnode = create_wnode(words[i]);
            new_knode->words = new_wnode;

            if (prev == NULL){ /*! If this key node fits into a place in the list before the root node, then it will be the new root node. */
                new_knode->nextNode = root;
                root = new_knode;
            }else{ /*! If this key node is between two nodes, it will be slot in accordingly. */
                prev->nextNode = new_knode;
                new_knode->nextNode = current;
            }

            /*! Sometimes, the key node will already exist in the linked list, so we will add that word to the word node linked in the key node. */

        }else{
            WNODE *new_wnode = create_wnode(words[i]);
            new_wnode->nextNode = current->words; /*! The order of the word nodes does not matter here. */
            current->words = new_wnode;
        }

        free(key);
    }
    return root;
}
            
void histogram(int *x, double *y, int n, int width);
double find_largest(double arr_of_no[], int len_of_arr);

void print_histogram(KNODE *a_list){

    /*! The following code creates the anagram count list to be printed for the histogram. */

    double ana_no_list[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; /*! Initialises the list that contains the number of key-anagram-pair variants per index. */
    int no_list[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    KNODE *currentk = a_list;
    while(currentk){
        WNODE *currentw = currentk->words;
        int count = 0;
        while(currentw){
            count++;
            currentw = currentw->nextNode;
        }
        ana_no_list[count]++; /*! Adds 1 to ana_no_list, the index of which corresponds to the number of anagrams the key has. */
        currentk = currentk->nextNode;
    }
            
    /* To find the biggest number in the anagram list. */
            
    int i;
    int biggest = ana_no_list[0];
    for(i = 1; i < 13; i++){
        if(ana_no_list[i] > biggest){
            biggest = ana_no_list[i];
        }
    }

    double biggest_log = log10((double)biggest);
    histogram(no_list, ana_no_list, 13, (int)biggest_log);
}
            
void print_anagram(KNODE *a_list){
    KNODE *currentk = a_list;
    int count_key = 0;
    int count_word = 0;
    int count_letter = 0;
    char *most_anagrams = NULL;
    char *longest_anagrams = NULL;
    char *longest_word1 = NULL;
    char *longest_word2 = NULL;
            
    while(currentk){
        int temp_count_letter = 0;
        WNODE *currentw = currentk->words;

        /*! The below works to find the longest pair of anagrams as well as the key with the most anagrams.
        * 
        * How it works (longest pair): it works by first assigning the very first key counted as the longest anagram, then comparing subsequent adjascent key lengths until the end of the array.
        * How it works (most anagrams): same as the longest pair, it works by assigning first the very first key as the one with the most anagrams, then comparing subsequent adjescent keys until the end of the array. */

        if(count_key == 0){ /*! If it is the first iteration in the array. */
            int temp_count_word = 0;
            while(currentw){
                temp_count_word++; /*! Counts the number of anagrams the key is associated with. */
                currentw = currentw->nextNode;
            }
            count_word = temp_count_word; /*! Assigns the temporary anagram count to a variable used for comparison. */
            longest_anagrams = currentk->key;
            count_letter = strlen(longest_anagrams); /*! Assigns the temporary letter count to a variable used for comparison. */

        }else{ /*! Subsequent iterations. What it does is basically compare the first key to subsequent keys, or the current key (which may not be the first) to subsequent keys. */
            int temp_count_word = 0;
            temp_count_letter = strlen(currentk->key);

            while(currentw){
                temp_count_word++;
                currentw = currentw->nextNode;
            }

            if(temp_count_word > count_word){
                count_word = temp_count_word;
                most_anagrams = currentk->key;
            }
            
            if(temp_count_word > 1 && (temp_count_letter > count_letter)){
                count_letter = temp_count_letter;
                longest_anagrams = currentk->key;
            }
        }
        count_key++; /*! After each loop in the list containing the keys, add so that it no longer triggers the first "if" condition. */
        currentk = currentk->nextNode;
    }
    
    /*! For the longest pair of anagrams, since the above code only compares key lengths, we must now find the anagrams associated with that key. */

    KNODE *traversek = a_list;
    while(traversek){
        if(traversek->key == longest_anagrams){
            WNODE *choosew = traversek->words;
            int countw = 0;
            while(choosew){
                if(countw == 0){
                    longest_word1 = choosew->word;
                    countw++;
                }else{
                    longest_word2 = choosew->word;
                    break;

                }
                choosew = choosew->nextNode;
            }
            break;
        }
        traversek = traversek->nextNode;
    }

    /*! Print our findings. */

    printf("%s has the largest number of variants.\n", most_anagrams);
    printf("%s and %s are the longest anagrams.\n", longest_word1, longest_word2);
}

int main(){
    int max_words 20506;
    int max_length_word 50;

    /*! Read file words.txt, works with the shorter list of words. */

    FILE *fp;
    if ((fp = fopen("words.txt", "r")) == NULL){
        fprintf(stderr, "Cannot open file.\n");
        exit(EXIT_FAILURE);
    }

    char words[max_words][max_length_word]; /*! Initialise array to contain the words in words.txt */
    WNODE wordNode;
    KNODE keyNode;
    int count = 0;

    while (count < max_words && fscanf(fp, "%s", words[count]) == 1){ /*! Reads all words in words.txt and adds them to array words. */
        count++;
    }

    /*! Initialises pointer array for words. */

    char **words_ptr = (char **)malloc(count * sizeof(char*));
    if (words_ptr == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    int i;
    for (i = 0; i < count; i++){
        words_ptr[i] = words[i];
    }

    /*! Creates anagram linked list of keys and anagrams and prints the longest pair, as well as the key with the most anagrams. */

    KNODE *a_list = make_anagram_list(words_ptr, count);

    print_anagram(a_list);

    print_histogram(a_list);

    free(words_ptr);
    fclose(fp);
    return EXIT_SUCCESS;
}