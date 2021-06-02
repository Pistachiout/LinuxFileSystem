# include "head.h"

void my_exitsys()
{
    /**
	 * 依次关闭 打开文件。 写入 FILENAME 文件
	 */
    while (currfd) {
        my_close(currfd);
    }
    FILE* fp = fopen(FILENAME, "w");
    fwrite(myvhard, SIZE, 1, fp);
    fclose(fp);
    printf("**************** exit file system ****************\n");
}
