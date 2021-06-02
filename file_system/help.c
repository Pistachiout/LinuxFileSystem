#include "head.h"

void help(char* command)
{
    if (strcmp(command, "my_mkdir") == 0){
        printf("%s\n", "use 'my_mkdir + dir_name' to create a dictionary");
    }
    else if(strcmp(command, "my_rmdir") == 0){
        printf("%s\n", "use 'my_rmdir dir_name' to remove a dictionary");
    }
    else if(strcmp(command, "my_ls") == 0){
        printf("%s\n", "use 'my_ls dir_name' to list contain in dictionary");
    }
    else if(strcmp(command, "my_cd") == 0){
        printf("%s\n", "use 'my_cd dir_name' to go to the dictionary");
    }
    else if(strcmp(command, "my_create") == 0){
        printf("%s\n", "use 'my_create file_name' to create a file");
    }
    else if(strcmp(command, "my_open") == 0){
        printf("%s\n", "use 'my_open file_name' to open a file");
    }
    else if(strcmp(command, "my_close") == 0){
        printf("%s\n", "use 'my_close file_name' to close the file");
    }
    else if(strcmp(command, "my_write") == 0){
        printf("%s\n", "use 'my_write file_name' to write contain to the file");
    }
    else if(strcmp(command, "my_read") == 0){
        printf("%s\n", "use 'my_read file_name' to read the file");
    }
    else if(strcmp(command, "my_rm") == 0){
        printf("%s\n", "use 'my_rm file_name' to rn the file");
    }
    else if(strcmp(command, "my_exit") == 0){
        printf("%s\n", "use 'my_exit' to exit the system");
    }
    else if(strcmp(command, "all") == 0){
        printf("%s\n", "use 'my_ls dir_name' to list contain in dictionary");
        printf("%s\n", "use 'my_mkdir + dir_name' to create a dictionary");
        printf("%s\n", "use 'my_rmdir dir_name' to remove a dictionary");
        printf("%s\n", "use 'my_cd dir_name' to go to the dictionary");
        printf("%s\n", "use 'my_create file_name' to create a file");
        printf("%s\n", "use 'my_open file_name' to open a file");
        printf("%s\n", "use 'my_close file_name' to close the file");
        printf("%s\n", "use 'my_write file_name' to write contain to the file");
        printf("%s\n", "use 'my_read file_name' to read the file");
        printf("%s\n", "use 'my_rm file_name' to rn the file");
        printf("%s\n", "use 'my_exit' to exit the system");
    }
    else {
        printf("%s\n", "command error");
    }
}

