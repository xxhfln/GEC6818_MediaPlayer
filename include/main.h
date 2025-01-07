#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

#include "show_bmp.h"
#include "touch.h"
#include "slow_slide.h"
#include "admin_login.h"
#include "list_user.h"
#include "manage_login.h"
#include "save_load.h"
#include "user_login.h"
#include "user_register.h"


//宏定义
#define MAX_USERNAME_LENGTH 10
#define MAX_PASSWORD_LENGTH 10
#define MAX_USERPHOTO_SUM 100
#define MAX_USERVIDEO_SUM 100
#define ADMIN_USERNAEM "infodba"
#define ADMIN_PASSWORD "infodba"
#define MAX_USER 10
// 全局变量
#define PIXELS 800*480 // 屏幕像素点
int x, y; // 触摸屏坐标变量
int fd_lcd; // LCD的文件描述符
int fd_touch; // touch文件
int *p_lcd; // LCD映射内存
int posx, posy; // 存放坐标

typedef struct 
{
    char username[MAX_USERNAME_LENGTH];
    char userpassword[MAX_USERNAME_LENGTH];
    char *userphoto[MAX_USERPHOTO_SUM];
    char *userviedo[MAX_USERVIDEO_SUM];
}User;

User  users[MAX_USER];
int user_count;

int project_init(void); // 程序初始化
int project_ui(void); // 程序主页面
int project_destroy(void); // 程序销毁
int project_touch(int *, int *);// 触摸屏操作函数


struct input_event buf; // 触摸屏结构体
// int open_serial(void);
// int PiccRequest(int fd);
// int init_mplayer();


#endif