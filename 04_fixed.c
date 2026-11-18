// demo 4: same as demo 1 but with snprintf so it cant overflow
// Build: gcc 04_fixed.c -o 04_fixed
#include <stdio.h>
#include <string.h>

struct user {
    char name[16];
    int  is_admin;
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <name>\n", argv[0]);
        return 1;
    }

    struct user u;
    u.is_admin = 0;

    // FIX: snprintf never writes more than sizeof(u.name) bytes
    // and always NUL-terminates. Excess input is truncated.
    int needed = snprintf(u.name, sizeof u.name, "%s", argv[1]);
    if (needed >= (int)sizeof u.name)
        fprintf(stderr, "warning: name truncated (%d chars given, max %zu)\n",
                needed, sizeof u.name - 1);

    printf("name     = \"%s\"\n", u.name);
    printf("is_admin = %d\n", u.is_admin);
    puts(u.is_admin ? ">>> ACCESS GRANTED: welcome, admin <<<" : "access denied");
    return 0;
}
