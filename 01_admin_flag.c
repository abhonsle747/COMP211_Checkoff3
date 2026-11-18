// demo 1: overflow name[] into the is_admin field right after it
// Build: gcc 01_admin_flag.c -o 01_admin_flag
#include <stdio.h>
#include <string.h>

struct user {
    char name[16];   // 16 bytes for the name...
    int  is_admin;   // ...and the flag sits right after it in memory
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <name>\n", argv[0]);
        return 1;
    }

    struct user u;
    u.is_admin = 0;

    printf("&u.name     = %p\n", (void *)u.name);
    printf("&u.is_admin = %p  (%ld bytes later)\n",
           (void *)&u.is_admin, (long)((char *)&u.is_admin - u.name));

    strcpy(u.name, argv[1]);   // BUG: no length check

    printf("name     = \"%s\"\n", u.name);
    printf("is_admin = %d (0x%08x)\n", u.is_admin, u.is_admin);
    puts(u.is_admin ? ">>> ACCESS GRANTED: welcome, admin <<<" : "access denied");
    return 0;
}
