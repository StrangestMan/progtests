#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int storedVal;

    struct testList *previous;
    struct testList *next;

} testList;

int main() {
    testList *valList = calloc(100, sizeof(*valList));
    if(valList == NULL) {
        fprintf(stderr, "Calloc call is brokey\n");
        return 1;
    }

    testList *cur;
    cur = valList;

    valList->storedVal = 0;
    valList->previous == NULL;
    valList->next = valList + 1;

    printf("testList + 0: %d\n", cur->storedVal);

    cur = valList->next;

    valList->storedVal = 10;
    valList->previous = valList + 0;
    valList->next == NULL;

    printf("testList + 1: %d\n", cur->storedVal);

    cur = cur->previous;

    //printf("testList + 1: %d\n", cur->next->storedVal);

    //printf("Linked test: %d", 10);



    return 0;
}