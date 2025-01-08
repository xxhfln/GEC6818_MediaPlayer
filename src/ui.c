#include "main.h"
#include "show_bmp.h"
#include <stdio.h>
#include <unistd.h>

// 菜单选择
int ChoiceSelect(void){
    int choice = 0;
    show_1152000bmp("./picture/Photo_tip.bmp", p_lcd);

    // 获取坐标
    int touch_mode = project_touch(&posx, &posy);

    if (posx >= 131 && posx <= 131+99 && posy >= 268 && posy <=268+128){
        return 1; // 图片
    }
    else if (posx >= 610 && posx <= 610+99 && posy >= 268 && posy <=268+143){
        return 2; // 视频
    }
    else if (posx >= 0 && posx <= 10+131 && posy >= 0 && posy <= 90){
        return 3; // 退出
    }
    else
        return 0;
}


// UI界面
int project_ui(void){
    //函数声明
    int Polling(int);
    int VideoPlay(int, int);

    show_1152000bmp("./picture/Photo_tip.bmp", p_lcd);

    // Polling(3);

    int choice;
    do {
        // 提示选择要进行的项目
        choice = ChoiceSelect();
        // printf("choice:%d\n", choice);
        switch (choice) {
            case 0:{
                break;
            }
            case 1:{ // 图片
                Polling(3);
                break;
            }
            case 2:{ // 视频
                VideoPlay(800, 400);
                break;
            }
            case 3:{
                return 0;
            }
            default:{
                printf("?");
                break;
            }
        }
    }
    while (1);

    return 0;
}