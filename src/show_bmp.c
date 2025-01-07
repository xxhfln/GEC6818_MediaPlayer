#include "show_bmp.h"
#include "main.h"
#include <stdio.h>
#include <strings.h>
#include <unistd.h>


/*
	功能：显示800*480大小的bmp图片。
	参数：
		char *pathname：要显示图片的名字。
		int *show_1152000bmp_fd：被映射区的指针。
	返回值：成功  0
			失败  -1
*/
int show_1152000bmp(char *pathname, int *show_1152000bmp_fd){
    // 打开BMP图片和LCD显示屏
    int fd_bmp = open(pathname, O_RDWR);
    if (fd_bmp == -1){
        perror("show_1152000bmp(),open bmp failed\n");
        return -1;
    }

    // 去除54字节
    int ret = lseek(fd_bmp, 54, SEEK_SET);
    if (ret == -1) {
        perror("show_1152000bmp(),lseek bmp failed\n");
        return -1;
    }

    // 读取BMP数据到LCD屏幕
    char bmp_buf[800 * 480 * 3];
    int lcd_buf[800 * 480];
    bzero(bmp_buf, 800 * 480 * 3);
    bzero(lcd_buf, 800 * 480);

    ret = read(fd_bmp, bmp_buf, 800 * 480 * 3);
    if (ret == -1){
        printf("show_1152000bmp(),read bmp failed\n");
        return -1;
    }
    close(fd_bmp);

    int i;
    for (i = 0; i < 800 * 480;i++){
        lcd_buf[i] = bmp_buf[i * 3] << 0 | bmp_buf[i * 3 + 1] << 8 | bmp_buf[i * 3 + 2] << 16;
    }

    int x, y;
    for (y = 0; y < 480;y++){
        for (x = 0; x < 800;x++){
            *(show_1152000bmp_fd + 800 * (479 - y) + x) = lcd_buf[800 * y + x];
        }
    }

    return 0;
}
 