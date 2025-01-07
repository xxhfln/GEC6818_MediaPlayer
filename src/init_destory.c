#include "file.h"
#include "main.h"
#include "save_load.h"
#include <stdio.h>

int project_init(void){
    // 打开LCD文件
    fd_lcd = open("/dev/fb0", O_RDWR);
    if (fd_lcd == -1){
        perror("open failed\n");
        return -1;
    }

    // 内存映射
    // LCD屏幕映射到p_lcd
    p_lcd = (int *)mmap(NULL, PIXELS * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_lcd, 0);
    if (*p_lcd == -1){
        perror("LCD mmap failed\n");
        return -1;
    }

    // 打开触摸屏文件
    fd_touch = open("/dev/input/event0", O_RDONLY);
    if (fd_touch == -1){
        perror("Open touch screen failed\n");
        return -1;
    }

    // 获取video文件夹下的所有视频文件
    int ret_ = getVideoFiles("./video");
    if (ret_ == -1){
        perror("getVideoFiles Error\n");
        return -1;
    }

    // user_count = 1; // 管理员
    load_user_data();

    return 0;
}

//程序项目关闭
int project_destroy(void){
    int ret;
    // 关闭LCD文件
    ret = close(fd_lcd);
    if (ret == -1){
        perror("Close LCD failed\n");
        return -1;
    }

    // 解除内存映射
    munmap(p_lcd, PIXELS * 4);

    // 关闭触摸屏文件
    ret = close(fd_touch);
    if (ret == -1){
        perror("Close touch screen failed\n");
        return -1;
    }

    return 0;
}
 