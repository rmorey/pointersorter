#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node{
    // pointer to the first char of the word in the input string
    char * word;
    struct Node* next;
} Node;


// Recursively insert the node into the linked list
Node* insert(Node* head, Node* n){
    if (head == NULL){
        return n;
    }
    if (strcmp(head->word,n->word) > 0){
        n->next = head;
        return n;
    }
    head->next = insert(head->next,n);
    return head;
}

void printlist(Node* head){
    while(head != NULL){
        printf("%s\n",head->word);
        head = head->next;
    }
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
    char* input = argv[1];
    printf("%s\n",input);
    int i;
    // Get to the first word
    for (i=0;!isalpha(input[i]);i++){
        if (input[i] == '\0'){
            exit(0);
        }
    }
    // Declare a Node pointer which will point to the head of the linked list
    Node* head = NULL; 
    int wordlen;
    while (input[i] != '\0'){
        wordlen = 0;
        while (isalpha(input[i])){
            i++;
            wordlen++;
        }
        Node* n = malloc(sizeof(Node));
        n->word = input + i - wordlen;
        n->word[wordlen] = '\0';
        i++;
        head = insert(head,n);
        if (input[i] == '\0'){
            break;
        }
        // Get to the next word
        while (!isalpha(input[i])){
            i++;
            if (input[i] == '\0'){
                break;
            }
        }
    }
    printlist(head);
	return 0;
}
