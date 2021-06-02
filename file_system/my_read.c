#include "head.h"

int my_read(int fd)
{
    if (fd < 0 || fd >= MAXOPENFILE) {
        printf("no such file\n");
        return -1;
    }

    openfilelist[fd].count = 0;
    char text[MAX_TEXT_SIZE] = "\0";
    do_read(fd, openfilelist[fd].length, text);
    printf("%s\n", text);
    return 1;
}