#include <stdio.h>
#include <string.h>

// Testing to see how chars work with strings

int main() {
    const char* testString = "This is a test string\n";
    for(char c = testString[0]; *testString; testString++) {
        c = *testString;
        printf("%c", c);
    }
    return 0;
}