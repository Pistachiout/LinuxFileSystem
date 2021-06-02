cmake_minimum_required(VERSION 3.17)
project(file_system C)

set(CMAKE_C_STANDARD 99)

add_executable(file_system main.c head.c head.h my_startsys.c
        my_exit.c my_format.c my_ls.c my_mkdir.c my_rmdir.c
        my_create.c my_rm.c my_open.c my_cd.c my_close.c
        my_read.c my_write.c do_read.c do_write.c
        get_free_openfilelist.c get_free_block.c help.c)