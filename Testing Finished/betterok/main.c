#include <stdio.h>
#include <stdlib.h>
#include "betterok.h"

int main() {
    const char *SAMPLE_TEXT = "This is some sample text;Try delimiting at different characters or strings of characters";
    const char *DELIM = ";";
    long int offset = 0;

    for(char *token = betterok(SAMPLE_TEXT, DELIM, &offset); token != NULL; token = betterok(SAMPLE_TEXT, DELIM, &offset)) {
        printf("%s\n", token);
        
        // I'm not certain if this is necessary, but I believe that not freeing the token leads to a memory leak, so I'm freeing it to be safe
        free(token);
    }

    return 0;
}