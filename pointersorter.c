#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
    if (argc < 2) {
        printf("Needs one argument, none given\n");
        exit(1);
    }
    if (argc > 2){
        printf("Too many arguments, needs exactly one\n");
        exit(1);
    }
    printf("The string is \"%s\"\n", argv[1]);
	return 0;
}
