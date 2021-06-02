#include "head.h"

void my_cd(char* dirname)
{
    int i = 0;
    int tag = -1;
    int fd;
    if (openfilelist[currfd].attribute == 1) {
        // if not a dir
        printf("you are in a data file, you could use 'my_close' to exit this file\n");
        return;
    }
    char* buf = (char*)malloc(10000);
    openfilelist[currfd].count = 0;
    do_read(currfd, openfilelist[currfd].length, buf);

    fcb* fcbptr = (fcb*)buf;
    // 查找目标 fcb
    for (i = 0; i < (int)(openfilelist[currfd].length / sizeof(fcb)); i++, fcbptr++) {
        if (strcmp(fcbptr->filename, dirname) == 0 && fcbptr->attribute == 0) {
            tag = 1;
            break;
        }
    }
    if (tag != 1) {
        printf("my_cd: no such dir\n");
        return;
    } else {
        // . 和 .. 检查
        if (strcmp(fcbptr->filename, ".") == 0) {
            return;
        } else if (strcmp(fcbptr->filename, "..") == 0) {
            if (currfd == 0) {
                // root
                return;
            } else {
                currfd = my_close(currfd);
                return;
            }
        } else {
            // 其他目录
            fd = get_free_openfilelist();
            if (fd == -1) {
                return;
            }
            openfilelist[fd].attribute = fcbptr->attribute;
            openfilelist[fd].count = 0;
            openfilelist[fd].date = fcbptr->date;
            openfilelist[fd].time = fcbptr->time;
            strcpy(openfilelist[fd].filename, fcbptr->filename);
            strcpy(openfilelist[fd].exname, fcbptr->exname);
            openfilelist[fd].first = fcbptr->first;
            openfilelist[fd].free = fcbptr->free;

            openfilelist[fd].fcbstate = 0;
            openfilelist[fd].length = fcbptr->length;
            strcat(strcat(strcpy(openfilelist[fd].dir, (char*)(openfilelist[currfd].dir)), dirname), "/");
            openfilelist[fd].topenfile = 1;
            openfilelist[fd].dirno = openfilelist[currfd].first;
            openfilelist[fd].diroff = i;
            currfd = fd;
        }
    }
}