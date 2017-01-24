#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct Nodes {
    char* string;
    struct Node* left;
    struct Node* right;
} Node;


int main(int argc, char * argv[]) {
    if (argc < 2) {
        printf("Needs one argument, none given\n");
        exit(1);
    }
    if (argc > 2){
        printf("Too many arguments, needs exactly one\n");
        exit(1);
    }
    char * input = argv[1];
    int wordlen;
    char * word;
    int i = 0;
    while (input[i] != '\0'){
        wordlen = 0;
        while (isalpha(input[i])){
            i++;
            wordlen++;
        }
        word = (char *)malloc(wordlen+1);
        memcpy(word,&input[i-wordlen],wordlen);
        word[wordlen] = '\0';
        printf("%s\n",word);
        if (input[i] == '\0'){
            exit(0);
        }
        while (!isalpha(input[i])){
            i++;
            if (input[i] == '\0'){
                exit(0);
            }
        }
    }
	return 0;
}
