// #include"user_login.h"
#include "file.h"
#include "main.h"
#include <string.h>

int user_login()
{
    char name[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("\n请输入用户名: ");
    scanf("%s",name);
    printf("请输入密码: ");
    system("stty -echo");
    scanf("%s", password);
    system("stty echo");
    printf("\n");
      // 检查用户名和密码
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, name) == 0 && strcmp(users[i].userpassword,password)== 0) {
            printf("登录成功!\n");
            // 这里可以实现查看用户图片视频的功能
            strcpy(user_path, USER_ROOT_DIR);
            strcat(user_path, name);
            strcpy(user_picture_path, user_path);
            strcpy(user_video_path, user_path);
            strcat(user_picture_path, "/picture/");
            strcat(user_video_path, "/video/");
            getVideoFiles(user_video_path);
            getPhotoFiles(user_picture_path);
            return 1;
        }
    }
    printf("用户名或密码错误\n");
    return 0;
}