#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Node in a linked list
typedef struct Node {
    char *word;                 // Not necessarily null terminated! 
    int len;
    struct Node *next;
} Node;

// Recursively insert the node into the linked list at *head_ptr
void insert(Node * n, Node ** head_ptr)
{
    Node *head = *head_ptr;
    if (head == NULL) {
        *head_ptr = n;
        return;
    }
    int min = (head->len < n->len) ? head->len : n->len;
    int cmp = strncmp(head->word, n->word, min);
    if (cmp == 0) {
        cmp = (head->len < n->len) ? -1 : 1;
    }
    if (cmp > 0) {
        n->next = head;
        *head_ptr = n;
    }
    if (cmp < 0) {
        insert(n, &(head->next));
    }
}

// Return a new node with the given word location and length. Return NULL
// if malloc() fails.
Node *create_node(char *word, int len)
{
    Node *n = (Node *) malloc(sizeof(Node));
    if (n != NULL) {
        n->word = word;
        n->len = len;
    }
    return n;
}

// Print the linked list.
void print_list(Node * head)
{
    Node *n;
    for (n = head; n != NULL; n = n->next) {
        printf("%.*s\n", n->len, n->word);
    }
}

// Free up the list memory.
void free_list(Node * head)
{
    Node *n, *next;
    for (n = head; n != NULL; n = next) {
        next = n->next;
        free(n);
    }
}

// Check if n is NULL, and if so free the list at head, and exit.
void null_check(Node * n, Node * head)
{
    if (n == NULL) {
        puts("ERROR: Malloc failed to allocate memory for Node");
        free_list(head);
        exit(-1);
    }
}

// parse the input string and return a Node which is the head of a sorted 
// linked list
Node *parse_input(char *input)
{
    char *ptr, *word;
    Node *head = NULL;
    for (ptr = input; *ptr != '\0'; ptr++) {
        if (isalpha(*ptr)) {
            for (word = ptr; isalpha(*ptr); ptr++) ;
            Node *n = create_node(word, ptr - word);
            null_check(n, head);
            insert(n, &head);
            ptr--;
        }
    }
    return head;
}

// Parse the input string, print the resulting list, then free its memory
int main(int argc, char *argv[])
{
    if (argc < 2) {
        puts("Needs one argument, none given");
        exit(1);
    }
    if (argc > 2) {
        puts("Too many arguments, needs exactly one");
        exit(1);
    }
    Node *head = parse_input(argv[1]);
    if (head != NULL) {
        print_list(head);
        free_list(head);
    }
    exit(0);
}
