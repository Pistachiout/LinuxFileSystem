#include "head.h"

void my_mkdir(char* dirname)
{
    /**
	 * 当前目录：当前打开目录项表示的目录
	 * 该目录：以下指创建的目录
	 * 父目录：指该目录的父目录
	 * 如:
	 * 我现在在 root 目录下， 输入命令 mkdir a/b/bb
	 * 表示 在 root 目录下的 a 目录下的 b 目录中创建 bb 目录
     * 这时，父目录指 b，该目录指 bb，当前目录指 root
	 * 以下都用这个表达，简单情况下，当前目录和父目录是一个目录
	 * 来不及了，先讨论简单情况，即 mkdir bb
	 */
    int i = 0;
    char text[MAX_TEXT_SIZE];

    char* fname = strtok(dirname, ".");
    char* exname = strtok(NULL, ".");
    if (exname != NULL) {
        printf("you can not use extension\n");
        return;
    }
    // 读取父目录信息
    openfilelist[currfd].count = 0;
    int filelen = do_read(currfd, openfilelist[currfd].length, text);
    fcb* fcbptr = (fcb*)text;

    // 查找是否重名
    for (i = 0; i < (int)(filelen / sizeof(fcb)); i++) {
        if (strcmp(dirname, fcbptr[i].filename) == 0 && fcbptr->attribute == 0) {
            printf("dir has existed\n");
            return;
        }
    }

    // 申请一个打开目录表项
    int fd = get_free_openfilelist();
    if (fd == -1) {
        printf("openfilelist is full\n");
        return;
    }
    // 申请一个磁盘块
    unsigned short int block_num = get_free_block();
    if (block_num == END) {
        printf("blocks are full\n");
        openfilelist[fd].topenfile = 0;
        return;
    }
    // 更新 fat 表
    fat* fat1 = (fat*)(myvhard + BLOCKSIZE);
    fat* fat2 = (fat*)(myvhard + BLOCKSIZE * 3);
    fat1[block_num].id = END;
    fat2[block_num].id = END;

    // 在父目录中找一个空的 fcb，分配给该目录  ??未考虑父目录满的情况??
    for (i = 0; i < (int)(filelen / sizeof(fcb)); i++) {
        if (fcbptr[i].free == 0) {
            break;
        }
    }
    openfilelist[currfd].count = i * sizeof(fcb);
    openfilelist[currfd].fcbstate = 1;
    // 初始化该 fcb
    fcb* fcbtmp = (fcb*)malloc(sizeof(fcb));
    fcbtmp->attribute = 0;
    time_t rawtime = time(NULL);
    struct tm* time = localtime(&rawtime);
    fcbtmp->date = (time->tm_year - 100) * 512 + (time->tm_mon + 1) * 32 + (time->tm_mday);
    fcbtmp->time = (time->tm_hour) * 2048 + (time->tm_min) * 32 + (time->tm_sec) / 2;
    strcpy(fcbtmp->filename, dirname);
    strcpy(fcbtmp->exname, "di");
    fcbtmp->first = block_num;
    fcbtmp->length = 2 * sizeof(fcb);
    fcbtmp->free = 1;
    do_write(currfd, (char*)fcbtmp, sizeof(fcb), 2);

    // 设置打开文件表项
    openfilelist[fd].attribute = 0;
    openfilelist[fd].count = 0;
    openfilelist[fd].date = fcbtmp->date;
    openfilelist[fd].time = fcbtmp->time;
    openfilelist[fd].dirno = openfilelist[currfd].first;
    openfilelist[fd].diroff = i;
    strcpy(openfilelist[fd].exname, "di");
    strcpy(openfilelist[fd].filename, dirname);
    openfilelist[fd].fcbstate = 0;
    openfilelist[fd].first = fcbtmp->first;
    openfilelist[fd].free = fcbtmp->free;
    openfilelist[fd].length = fcbtmp->length;
    openfilelist[fd].topenfile = 1;
    strcat(strcat(strcpy(openfilelist[fd].dir, (char*)(openfilelist[currfd].dir)), dirname), "/");

    // 设置 . 和 .. 目录
    fcbtmp->attribute = 0;
    fcbtmp->date = fcbtmp->date;
    fcbtmp->time = fcbtmp->time;
    strcpy(fcbtmp->filename, ".");
    strcpy(fcbtmp->exname, "di");
    fcbtmp->first = block_num;
    fcbtmp->length = 2 * sizeof(fcb);
    do_write(fd, (char*)fcbtmp, sizeof(fcb), 2);

    fcb* fcbtmp2 = (fcb*)malloc(sizeof(fcb));
    memcpy(fcbtmp2, fcbtmp, sizeof(fcb));
    strcpy(fcbtmp2->filename, "..");
    fcbtmp2->first = openfilelist[currfd].first;
    fcbtmp2->length = openfilelist[currfd].length;
    fcbtmp2->date = openfilelist[currfd].date;
    fcbtmp2->time = openfilelist[currfd].time;
    do_write(fd, (char*)fcbtmp2, sizeof(fcb), 2);

    // 关闭该目录的打开文件表项，close 会修改父目录中对应该目录的 fcb 信息
    /**
	 * 这里注意，一个目录存在 2 个 fcb 信息，一个为该目录下的 . 目录文件，一个为父目录下的 fcb。
	 * 因此，这俩个fcb均需要修改，前一个 fcb 由各个函数自己完成，后一个 fcb 修改由 close 完成。
	 * 所以这里，需要打开文件表，再关闭文件表，实际上更新了后一个 fcb 信息。
	 */
    my_close(fd);

    free(fcbtmp);
    free(fcbtmp2);

    // 修改父目录 fcb
    fcbptr = (fcb*)text;
    fcbptr->length = openfilelist[currfd].length;
    openfilelist[currfd].count = 0;
    do_write(currfd, (char*)fcbptr, sizeof(fcb), 2);
    openfilelist[currfd].fcbstate = 1;
}