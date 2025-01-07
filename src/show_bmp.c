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

void draw_point(int x, int y, int color, int *addr){
    if (x >= 0 && x < 800 && y >= 0 && y < 480) {
        *(addr + 800 * y + x) = color;
    }
}

int show_bmp(const char *path, int *addr, int x_w, int y_h){
    int bmp_size, bmp_width, bmp_height;
    
    // 获取图片数据
    int bmp_fd = open(path, O_RDONLY);
    if (bmp_fd == -1){
        perror("open failed");
        return -1;
    }

    lseek(bmp_fd, 18, SEEK_SET);
    read(bmp_fd, &bmp_width, 4);
    read(bmp_fd, &bmp_height, 4);

    printf("bmp_width = %d\n", bmp_width);
    printf("bmp_height = %d\n", bmp_height);

    // 获取图片颜色数据
    char bmp_color[bmp_width * bmp_height * 3];
    lseek(bmp_fd, 54, SEEK_SET);
    int ret = read(bmp_fd, bmp_color, sizeof(bmp_color));
    if (ret == -1){
        perror("read err\n");
        return -1;
    }
    close(bmp_fd);

    //字节对齐处理
    int row_size = bmp_width * 3;
    int add = 0;
    if (row_size % 4 != 0){
        add = 4 - row_size % 4;
    }

    //颜色数据顺序处理
    int lcd_color[bmp_width * bmp_height];
    char *pos = bmp_color;
    for (int y = 0; y < bmp_height;y++){
        for (int x = 0; x < bmp_width;x++){
            lcd_color[x + y * bmp_width] = pos[0] | pos[1] << 8 | pos[2] << 16 | 0x00 << 24;
            pos += 3;
        }
        pos += add; // 无法整除4,下一排
    }

    // 将图片像素点颜色数据映射到lcd屏幕中
    for (int y = 0; y < bmp_height;y++){
        for (int x = 0; x < bmp_width;x++){
            draw_point(x + x_w, y + y_h, lcd_color[x + (bmp_height - 1 - y) * bmp_width], addr);
        }
    }
    return 0;
}
 