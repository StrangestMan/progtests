#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define newvar(type, name) type name

int main() {
    newvar(char*, lmao);
    lmao = malloc(10 * sizeof(lmao));
    
    if(lmao == NULL) {
        printf("It brokey\n");
        return 1;
    }

    strcpy(lmao, "lmao");

    printf("lmao: %s\n", lmao);

    return 0;
}