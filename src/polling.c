#include "main.h"
#include "show_bmp.h"
#include <stdio.h>

int Polling(int delay)
{
    char *bmpname[5] = {"./picture/1.bmp", "./picture/2.bmp", "./picture/3.bmp", "./picture/4.bmp", "./picture/5.bmp"};
    int bmpnum = 0;
    int choice;
    show_1152000bmp(bmpname[0], p_lcd);
    do {
        int nTouch = project_touch(&posx, &posy);
        if((nTouch == 0 && posx > 400) || nTouch == 2){// 点击到了右边或者左划
            choice = 1;
        }else if ((nTouch == 0 && posx < 400) || nTouch == 1){// 点击到了左边或者右划
            choice = 2;
        }else if (nTouch == 4){ // 上划
            choice = 0;
        }

        switch (choice) {
            case 0:{
                printf("Exit!\n");
                show_1152000bmp("./picture/Photo_tip.bmp", p_lcd);
                break;
            }
            case 1:{
                if (bmpnum == 4) {
                    printf("This is the last picture\n");
                    bmpnum = -1;
                }
                bmpnum += 1;
                show_1152000bmp(bmpname[bmpnum], p_lcd);
                break;
            }
            case 2:{
                if (bmpnum == 0){
                    printf("This is the first picture\n");
                    bmpnum = 5;
                }
                bmpnum -= 1;
                show_1152000bmp(bmpname[bmpnum], p_lcd);
                break;
            }
            default:{
                printf("Error\n");
                break;
            }
        }
    }
    while (choice != 0);


    return 0;
}
 