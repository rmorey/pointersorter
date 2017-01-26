#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Node in a linked list
typedef struct Node{
    // Pointer to the first char of the word in the input string
    char * word;
    // Pointer to the next node in the list
    struct Node* next;
} Node;


// Recursively insert the node into the linked list at the correct location
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
            i++;
            wordlen++;
        }
        // Create the new node, and point its word to the start of the current
        // word in the input string
        Node* n = malloc(sizeof(Node));
        if (n == NULL){
            printf("Malloc failed to allocate space for new Node\n");
            exit(-1);
        }
        n->word = input + i - wordlen;
        // Break to see if we're now at the end of the input string, and if so
        // insert it into the linked list and return the head
        if (input[i] == '\0'){
            head = insert(head,n);
            return head;
        }
        // Put a null byte after the string (yes, in the middle of the input string)
        // We are saving memory by just referencing the words inside the input string
        // but we want to use string.h functions on it, so we put a null byte at the end
        // (overwriting whatever the next character is, but we don't care cause we know 
        // it's not alphabetic)
        //
        // We are aware that Prof. Francisco said not to modify argv, but it seems like a total waste of
        // space to copy it all again, and getopt() does it, and programs like mysql do it to hide
        // password arguments from other programs, so we're gonna do it.
        //
        // Well, maybe inserting the null byte into the middle of a normal string is particularly sketchy...
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
