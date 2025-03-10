#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct wordNode {
        char *word;
        struct wordNode *nextNode;
} WNODE;

typedef struct keyNode {
        char *key;
        WNODE *words;
        struct keyNode *nextNode;
} KNODE;

WNODE *create_wnode(char *word);
KNODE *create_knode(char *key);
void sortalpha(char *word);
KNODE *make_anagram_list(char **words, int n);

void print_anagrams(char *word_entered, KNODE *a_list){ /*! This function prints all anagrams of a given word. */
        KNODE *currentk = a_list;
        sortalpha(word_entered);
        while(currentk){
            if(strcmp(currentk->key, word_entered) == 0){
                WNODE *currentw = currentk->words;
                while(currentw){
                    printf("%s\n", currentw->word);
                    currentw = currentw->nextNode;
                }
            break;
            }else{
                currentk = currentk->nextNode;
            }
        }
    }

int main(){
        int max_words = 20506;
        int max_length_word = 45;
    
        int neverending = 0;
        char word_entered[45];
        while(neverending == 0){ /*! Since neverending will never be more than 0, this will keep going. */
            printf("Enter a word: ");
            if(scanf("%s", word_entered) == 1){
                printf("Anagrams are:\n");
    
                FILE *fp;
                if ((fp = fopen("shorter_words.txt", "r")) == NULL){
                    fprintf(stderr, "Cannot open file.\n");
                    exit(EXIT_FAILURE);
                }
    
                WNODE wordNode;
                KNODE keyNode;
                char words[max_words][max_length_word];
                int count = 0;
    
                while(count < max_words && fscanf(fp, "%s", words[count]) == 1){ /*! This reads each line of words.txt and adds it as one element into the array words. */
                    count++;
                }
    
                /*! The following converts the words array into a pointer called words_ptr. */
    
                char **words_ptr = (char **)malloc(count * sizeof(char*));
                if (words_ptr == NULL){
                    fprintf(stderr, "Memory allocation failed.\n");
                    return 1;
                }
                int i;
                for (i = 0; i < count; i++){
                    words_ptr[i] = words[i];
                }
    
                /*! After making linked lists of anagrams called a_list using make_anagram_list, use print_anagrams to print all the anagrams of the word input in the beginning. */
    
                KNODE *a_list = make_anagram_list(words_ptr, count);
                print_anagrams(word_entered, a_list);
    
                free(words_ptr); 
                fclose(fp);
            }else{
                printf("Error.\n"); /*! Error handling. */
            }
        }
        return 0;
}