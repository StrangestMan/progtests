#include <stdio.h>
#include <stdarg.h>

int add(const int numargs, ...);

int main() {
    return 0;
}

int add(const int numargs, ...) {
    va_list args;
    va_start(args, numargs);

    int result = 0;
    for(int i = 0; i < numargs; i++) {
        result += va_arg(args, int);
    }

    va_end(args);
    return result;
}