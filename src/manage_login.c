// #include"manage_login.h"
#include "main.h"

void display_menu() {
    printf("\n===== 电子相册系统 =====\n");
    printf("1. 注册用户\n");
    printf("2. 用户登录\n");
    printf("3. 管理员登录\n");
    printf("4. 退出\n");
}

int manage_login()
{
    int choice;
    while(1)
    {
        display_menu();
        printf("输入数字选择：\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:{
                system("clear");
                user_register();
                break;
            }
            case 2:{
                system("clear");
                if(user_login() == 1){
                    return 0;
                }
            }
            case 3:{
                system("clear");
                if(admin_login() == 1)
                {
                    list_user();
                    return 0;
                }
            }
            case 4:{
                printf("电子相册正在退出中.....\n");
                save_user_data();
                return -1;
            }
            default:
                printf("无效选择，请重新选择\n");

        };
    };

    return 0;
}
