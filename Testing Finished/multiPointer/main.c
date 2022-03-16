#include <stdio.h>
#include <stdlib.h>

int main() {
    int ***a = NULL, **b = NULL, *c = NULL;
    int val = 10;

    // A points to B, points to C, points to Val

    a = &b;
    b = &c;
    c = &val;

    ***a = 11;

    printf("Val through a multi-level pointer: %d\n", ***a);
    return 0;
}

    // Takeaway: You need as many stars (*) as you have poitners to point to.
        // A can point to 3 different values, the address of b, the address of c, and the value of val, so it gets 3 stars
        // B can point to 2 different values, the address of c, and the value of val, so it gets 2 stars
        // C can point only to 1 value, the address of / value of val, so it gets 1 star

        // Dereferencing a multi-level pointer is done by using different numbers of stars
            // a = the address of b
            // *a = the value of b (the address of c)
            // **a = the value of c (the address of val)
            // ***a = the value of var (the value we care about)