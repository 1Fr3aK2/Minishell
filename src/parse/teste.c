#include "../../includes/shellinho.h"
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char *dest;
    char *s = "PATH";
    dest = getenv(s);
    printf("%s\n", dest);
}