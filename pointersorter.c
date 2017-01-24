#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Nodes {
    char* word;
    struct Node* next;
} Node;

int isnull(char c){
    return (c == '\0');
}

Node* insert(Node* root, Node* n){
    if (root == NULL){
        return n;
    }
    if (strcmp(root->word,n->word) > 0){
        n->next = root;
        return n;
    }
    root->next = insert(root->next,n);
    return root;
}


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
    int i;
    for (i=0;!isalpha(input[i]);i++){
        if isnull(input[i]){
            exit(0);
        }
    }
    Node* root = NULL;
    while (!isnull(input[i])){
        wordlen = 0;
        while (isalpha(input[i])){
            i++;
            wordlen++;
        }
        Node n;
        n->word = (char *)malloc(wordlen+1);
        memcpy(n->word,&input[i-wordlen],wordlen);
        n->word[wordlen] = '\0';
        root = insert(root,n)
        if (isnull(input[i])){
            exit(0);
        }
        while (!isalpha(input[i])){
            i++;
            if (isnull(input[i])){
                exit(0);
            }
        }
    }
	return 0;
}
