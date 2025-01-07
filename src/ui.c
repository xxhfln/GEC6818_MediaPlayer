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

    if (posx >= 128 && posx <= 128+237 && posy >= 244 && posy <=244+154){
        return 1; // 图片
    }
    else if (posx >= 436 && posx <= 436+237 && posy >= 244 && posy <=244+154){
        return 2; // 视频
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
        switch (choice) {
            case 0:{
                break;
            }
            case 1:{ // 图片
                Polling(3);
                break;
            }
            case 2:{ // 视频
                // int count = 0;
                // while (count < 5) {
                //     show_1152000bmp("./picture/2.bmp", p_lcd);
                //     count++;
                //     sleep(1);
                // }
                VideoPlay(800, 400);
                break;
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