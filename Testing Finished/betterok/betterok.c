#include "betterok.h"
#include <stdlib.h>
#include <string.h>

char* betterok(const char *STRING, const char *DELIM, long int *offset) {
    // Return string for later
    char *retstring = NULL;
    
    // Sizes of const strings
    const long int DELIM_SIZE = strlen(DELIM);
    const long int STRING_RSIZE = rstrlen(STRING);

    // Create string for manipulation
    char *manipstr = calloc(STRING_RSIZE, sizeof(char));
    strncpy(manipstr, STRING, STRING_RSIZE - 1);

    // Size of manipstr for later
    long int size = strlen(manipstr);

    // Check to make sure offset isn't outside the range of the string (if the offset starts on null then just return null because it wont find anything)
    if(*offset > size) {
        return NULL;
    }

    // Go to the desired offset
    manipstr += *offset;

    // Check entire string for delimiter or end of string
    long int index = *offset;
    for(long int inc = 0; index <= size; manipstr++, index++, inc++) {
        if(strncmp(manipstr, DELIM, DELIM_SIZE) == 0 || *manipstr == '\0') {
            manipstr -= inc;
            retstring = calloc(inc + 1, sizeof(char));
            strncpy(retstring, manipstr, inc);

            *offset += inc + 1;
            return retstring;
        }
    }

    return NULL;
}

// I could use strlen here, but I wanted to do something different. If strlen is faster, I'll change this

// Turns out strlen is faster. I should look at it's implementation sometime. Maybe compiling as -O3 would make it faster. 

// Nope still slower. Strlen it is
long int rstrlen(const char *STRING) {
    return strlen(STRING) + 1;
}