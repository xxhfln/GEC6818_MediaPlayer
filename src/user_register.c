// #include"user_register.h"
// #include "save_load.h"
#include "file.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

    char temp[MAX_FILENAME_LENGTH] = {'\0'};
    strcpy(temp, USER_ROOT_DIR);
    strcat(temp, name);
    if (newFolder(temp) == -1){
        printf("%s用户文件夹创建失败\n", name);
        return -1;
    }
    char temp_2[MAX_FILENAME_LENGTH] = {'\0'};
    strcpy(temp_2, temp);
    strcat(temp, "/picture");
    strcat(temp_2, "/video");
    if (newFolder(temp) == -1 || newFolder(temp_2) == -1){
        printf("%s用户picture文件夹或video文件夹创建失败\n", name);
        return -1;
    }
    sleep(1);
    return 1;
}
