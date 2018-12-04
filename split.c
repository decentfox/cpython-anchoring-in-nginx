#include <stdio.h>

char *get_world() {
    return "world";
}

int main() {
    printf("Hello, %s!\n", get_world());
}
