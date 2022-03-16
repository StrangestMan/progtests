#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *msg;
    int msgLength;
    
} message;

int main() {

    // Truly jagged array (dynamically allocated jagged array) with ints
    int **arr;
    arr = malloc(4 * sizeof(int*));

    arr[0] = malloc(10 * sizeof(int));
    arr[1] = malloc(2 * sizeof(int));
    arr[2] = malloc(30 * sizeof(int));
    arr[3] = malloc(100 * sizeof(int));

    arr[0][3] = 10;
    arr[1][0] = 2;
    arr[2][50] = 99;

    printf("Numbers from the array: %d, %d, %d\n", arr[0][3], arr[1][0], arr[2][50]);

    // Truly jagged array (dynamically allocated jagged array) with strings
    char **chararr;
    chararr = malloc(2 * sizeof(char*)); // Defines the first dimension

    chararr[0] = malloc(50 * sizeof(char)); // Defines the second dimension of the first row
    chararr[1] = malloc(10 * sizeof(char)); // Defines the second dimension of the second row

    strcpy(chararr[0], "This is a string that can contain 50 characters");
    strcpy(chararr[1], "10 char");

    printf("String 1: %s\n", chararr[0]);
    printf("String 2: %s\n", chararr[1]);

    // Three dimensional jagged array (in chars)
    char ***threed;
    const int d1 = 3;
    const int d2 = 2;
    
    threed = malloc(d1 * sizeof(char**));

    for(int i = 0; i < d1; i++) {
        threed[i] = malloc(d2 * sizeof(char*));
    }

    message msgArr[6] = {
        {"This is a constant message", strlen(msgArr[0].msg) + 1},
        {"And so is this", strlen(msgArr[1].msg) + 1},
        {"All of these are constant strings", strlen(msgArr[2].msg) + 1},
        {"You can't change them", strlen(msgArr[3].msg) + 1},
        {"but that's fine", strlen(msgArr[4].msg) + 1},
        {"they just needed to be of varrying lengths to test a point", strlen(msgArr[5].msg) + 1}
    };
    int msgIndex = 0;

    for(int i = 0; i < d1; i++) {
        for(int j = 0; j < d2; j++) {
            threed[i][j] = malloc(msgArr[msgIndex].msgLength * sizeof(char));
            msgIndex++;
        }
    }

    msgIndex = 0;
    for(int i = 0; i < d1; i++) {
        for(int j = 0; j < d2; j++) {
            strcpy(threed[i][j], msgArr[msgIndex].msg);
            msgIndex++;
        }
    }

    int msgNum = 1;
    for(int i = 0; i < d1; i++) {
        for(int j = 0; j < d2; j++) {
            printf("Message %d after copying: %s\n", msgNum, threed[i][j]);
            msgNum++;
        }
    }

    // strlen testing
    char *teststr;
    teststr = malloc(4096 * sizeof(char));
    strcpy(teststr, "lmao");

    printf("Length of teststr (including null char): %ld\n", strlen(teststr) + 1);

    return 0;
}