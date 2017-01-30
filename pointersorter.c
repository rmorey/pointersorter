#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Node in a linked list
struct Node {
    char *word;
    int len;
    struct Node *next;
};

// Recursively insert the node into the linked list and return the head of the list
struct Node *insert(struct Node *head, struct Node *n)
{
    if (head == NULL) {
        return n;
    }
    int min = (head->len < n->len) ? head->len : n->len;
    int cmp = strncmp(head->word, n->word, min);
    if (cmp == 0) {
        cmp = (head->len < n->len) ? -1 : 1;
    }
    if (cmp < 0) {
        head->next = insert(head->next, n);
    }
    if (cmp > 0) {
        n->next = head;
        head = n;
    }
    return head;
}

// Create a node with the given word location and length
struct Node *create_node(char *word, int len)
{
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    if (n != NULL) {
        n->word = word;
        n->len = len;
    }
    return n;
}

void print_list(struct Node *head)
{
    struct Node *n;
    for (n = head; n != NULL; n = n->next){
        printf("%.*s\n", n->len, n->word);
    }            
}

void free_list(struct Node *head)
{
    struct Node *n = head;
    struct Node *next;
    while (n != NULL) {
        next = n->next;
        free(n);
        n = next;
    }
}

void null_check(struct Node *n, struct Node *head) {
    if (n == NULL){
        puts("ERROR: Malloc failed to allocate memory for Node");
        free_list(head);
        exit(-1);
    }
}

// parse the input string and return a Node which is the head of a sorted linked list
struct Node *parse_input(char *input)
{
    char *ptr = input;
    char *word;
    struct Node *head = NULL;
    for (ptr = input; *ptr != '\0'; ptr++) {
        if (isalpha(*ptr)) {
            for (word = ptr; isalpha(*ptr); ptr++) ;
            struct Node *n = create_node(word, ptr - word);
            null_check(n, head);
            head = insert(head, n);
            ptr--;
        }
    }
    return head;
}

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
    struct Node *head = parse_input(argv[1]);
    print_list(head);
    free_list(head);
    return 0;
}
