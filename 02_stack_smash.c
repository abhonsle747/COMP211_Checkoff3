// demo 2: overflow a local buffer way past the end so it hits the return address
// Build: gcc 02_stack_smash.c -o 02_stack_smash
// note: gcc on ubuntu turns on the stack canary by default, so this should
// print "stack smashing detected" instead of returning normally
#include <stdio.h>
#include <string.h>

void greet(const char *input) {
    char buf[16];
    strcpy(buf, input);        // BUG: input can be longer than 16 bytes
    printf("Hello, %s\n", buf);
}                              // return address is read back here

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <name>\n", argv[0]);
        return 1;
    }
    greet(argv[1]);
    puts("greet() returned normally");
    return 0;
}
