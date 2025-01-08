// #include"admin_login.h"
#include "main.h"

int admin_login()
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
        if (strcmp(name, ADMIN_USERNAEM) == 0 && strcmp(password,ADMIN_PASSWORD) == 0)
            printf("登录成功!\n");
        // 这里可以实现查看用户图片视频的功能
        return 1;
    }
    printf("用户名或密码错误\n");
    return 0;
}
        
        
