// #include"user_register.h"
// #include "save_load.h"
#include "main.h"

int user_register()
{
    char name[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("\n请输入注册用户名: ");
    scanf("%s", name);
    printf("请输入注册密码: ");
    scanf("%s",password);
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, name) == 0) {
            printf("该用户名已被注册\n");
            return 0;
        }
    }
    strcpy(users[user_count].username, name);
    strcpy(users[user_count].userpassword,password);// 使用盐值加密密码
    user_count++;
    printf("注册成功！！！");
    save_user_data();
    return 1;
}
