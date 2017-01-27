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
    if (n == NULL) {
        puts("Malloc failed to allocate space for new Node");
        exit(-1);
    }
    n->word = word;
    n->len = len;
    return n;
}

struct Node *insert_word(struct Node *head, char *word, int len)
{
    return insert(head, create_node(word,len));
}

void print_list(struct Node *head)
{
    if (head == NULL) {
        return;
    }
    printf("%.*s\n", head->len, head->word);
    print_list(head->next);
}

void free_list(struct Node *head)
{
    if (head == NULL) {
        return;
    }
    if (head->next != NULL) {
        free_list(head->next);
    }
    free(head);
}

// parse the input string and return a Node which is the head of a sorted linked list
struct Node *parse_input(char *input)
{
    char *ptr = input;
    struct Node *head = NULL;
    char *word;
    while (1) {
        while (!isalpha(*ptr)) {
            if (*ptr == '\0') {
                return head;
            }
            ptr++;
        }
        for (word = ptr; isalpha(*ptr); ptr++) ;
        head = insert_word(head, word, ptr - word);
    }
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
