#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Node in a linked list
typedef struct Node{
    // pointer to the first char of the word in the input string
    char * word;
    // Pointer to the next node in the list
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

// print the list
void printlist(Node* head){
    while(head != NULL){
        printf("%s\n",head->word);
        head = head->next;
    }
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
    int i;
    // Get to the first word
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
            i++;
            wordlen++;
        }
        // Create the new node, and point to its word
        Node* n = malloc(sizeof(Node));
        n->word = input + i - wordlen;
        // Check to see if we're now at the end of the input string
        if (input[i] == '\0'){
            head = insert(head,n);
            break;
        }
        // Put a null byte after the string (yes, in the middle of the input string)
        // we are saving memory by just referencing the word in the input string
        // but we want to use string.h functions on it, so we put a null byte
        n->word[wordlen] = '\0';
        // insert the node into the linked list
        head = insert(head,n);
        i++;
        // Get to the next word
        while (!isalpha(input[i])){
            if (input[i] == '\0'){
                return head;
            }
            i++;
        }
    }
    return head;
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
    printlist(head);
    freelist(head);
	return 0;
}
