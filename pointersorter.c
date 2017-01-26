#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Node in a linked list
typedef struct Node{
    // Pointer to the first char of the word in the input string
    char * word;
    // Length of the word
    int len;
    // Pointer to the next node in the list
    struct Node* next;
} Node;


// Recursively insert the node into the linked list at the correct location
Node* insert(Node* head, Node* n){
    if (head == NULL){
        return n;
    }
    // get the min length of the two strings
    int min = (head->len < n->len) ? head->len : n->len;
    // compare up to the end of the shorter string
    int cmp = strncmp(head->word,n->word,min);
    // If they are equal for min bytes, then we want to put the 
    // shorter one first (it doesn't matter which goes first
    // if they are equal in length)
    if (cmp == 0){ 
        cmp = (head->len < n->len) ? -1 : 1;
    }
    if (cmp < 0){
        head->next = insert(head->next,n);
    }
    if (cmp > 0){
        n->next = head;
        head = n;
    }
    return head;
}


// print the list
void printlist(Node* head){
    if (head == NULL){
        return;
    }
    printf("%.*s\n",head->len,head->word);
    printlist(head->next);
}
    

// free up all the list memory, recursively
void freelist(Node* head){
    if (head == NULL){
        return;
    }
    if (head->next != NULL){
        freelist(head->next);
    }
    free(head);
}

// parse the input string and return a Node which is the head of a sorted linked list
Node* parseinput(char * input){
    // i keeps track of our location in the input string
    int i;
    // Get to the first word, return null if we reach the end of the string
    for (i=0;!isalpha(input[i]);i++){
        if (input[i] == '\0'){
            return NULL;
        }
    }
    // Declare a Node pointer which will point to the head of the linked list
    Node* head = NULL; 
    int wordlen;
    while (1){
        wordlen = 0;
        // Get to the end of the current word
        while (isalpha(input[i])){
            wordlen++;
            i++;
        }
        // Create the new node, and point its word to the start of the current
        // word in the input string
        Node* n = (Node*)malloc(sizeof(Node));
        if (n == NULL){
            printf("Malloc failed to allocate space for new Node\n");
            exit(-1);
        }
        // instead of copying the string, we just point to its location
        // in the input string and keep track of the length 
        n->word = input + i - wordlen; // slick pointer arithmetic
        n->len = wordlen;
        // insert the node into the linked list
        head = insert(head,n);
        // Get to the next word
        while (!isalpha(input[i])){
            if (input[i] == '\0'){
                return head;
            }
            i++;
        }
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
    // Parse the input into a sorted linked list

    Node* head = parseinput(argv[1]);
    // Print the linked list
    printlist(head);
    // free up the memory
    freelist(head);
	return 0;
}
