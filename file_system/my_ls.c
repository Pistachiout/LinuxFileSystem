#include "head.h"

void my_ls()
{
    // 判断是否是目录
    if (openfilelist[currfd].attribute == 1) {
        printf("data file\n");
        return;
    }
    char buf[MAX_TEXT_SIZE];
    int i;

    // 读取当前目录文件信息(一个个fcb), 载入内存
    openfilelist[currfd].count = 0;
    do_read(currfd, openfilelist[currfd].length, buf);

    // 遍历当前目录 fcb
    fcb* fcbptr = (fcb*)buf;
    for (i = 0; i < (int)(openfilelist[currfd].length / sizeof(fcb)); i++, fcbptr++) {
        if (fcbptr->free == 1) {
            if (fcbptr->attribute == 0) {
                if (strcmp(fcbptr->filename,"..") &&strcmp(fcbptr->filename,"."))
                {      printf("<DIR> %-8s\t%d/%d/%d %d:%d\n",
                       fcbptr->filename,
                       (fcbptr->date >> 9) + 2000,
                       (fcbptr->date >> 5) & 0x000f,
                       (fcbptr->date) & 0x001f,
                       (fcbptr->time >> 11),
                       (fcbptr->time >> 5) & 0x003f);}
            } else {
                printf("<FILE> %-8s\t%d/%d/%d %d:%d\t%d\n",
                       fcbptr->filename,
                       (fcbptr->date >> 9) + 2000,
                       (fcbptr->date >> 5) & 0x000f,
                       (fcbptr->date) & 0x001f,
                       (fcbptr->time >> 11),
                       (fcbptr->time >> 5) & 0x003f,
                       fcbptr->length);
            }
        }
    }
}