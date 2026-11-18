// demo 3: print addresses of different parts of memory. run it a few times (ASLR)
// Build: gcc 03_aslr.c -o 03_aslr
#include <stdio.h>
#include <stdlib.h>

int global_var = 42;

int main(void) {
    int  local_var = 7;
    int *heap_var  = malloc(sizeof *heap_var);

    printf("code  (main)   : %p\n", (void *)main);
    printf("data  (global) : %p\n", (void *)&global_var);
    printf("heap  (malloc) : %p\n", (void *)heap_var);
    printf("stack (local)  : %p\n", (void *)&local_var);
    printf("libc  (printf) : %p\n", (void *)printf);

    free(heap_var);
    return 0;
}
