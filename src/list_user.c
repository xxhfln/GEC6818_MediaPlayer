// #include"list_user.h"
#include "main.h"

int list_user()
{
    printf("\n===== 所有用户信息 =====\n");
    for (int i = 0; i < user_count; i++) {
        printf("用户名: %s\n", users[i].username);
        // 这里可以继续列出图片和视频等信息
    }
}