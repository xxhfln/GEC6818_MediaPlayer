#include "main.h"
#include "show_bmp.h"
#include "touch.h"
#include <stdio.h>
#include <stdlib.h>

int VideoPlay(char *video_path, int width, int height)
{
    show_bmp("./picture/zanting.bmp", p_lcd, 0, 400);

    // 打开视频文件
    system("killall -9 mplayer");
    char Video[255];
    sprintf(Video,
            "mplayer -slave -quiet -input file=/fifo -geometry 0:0 -zoom -x %d -y %d -loop 0 "
            "-framedrop -cache 8192 -lavdopts lowres=1:fast:skiploopfilter=all %s &",
            width,
            height,
            video_path);
    system(Video);

    // 操作视频
    int posx_, posy_;
    int choice;
    int video_mode = 1;
    do {
        int nTouch = project_touch(&posx_, &posy_);
        if (nTouch == 0){
            choice = 1; // 暂停或继续视频
            int video_touch = VideoTouch(posx_, posy_);
            if (video_touch == 1){
                
            }
        }
        else if (nTouch == 4){
            choice = 2; // 退出视频
        }

        switch (choice) {
            case 0:{
                system("killall -SIGKILL mplayer");
                break;
            }
            case 1:{ // 暂停/继续
                if (video_mode == 1){
                    printf("暂停播放\n");
                    system("killall -SIGSTOP mplayer");
                    video_mode = 0;
                } else {
                    printf("继续播放\n");
                    system("killall -SIGCONT mplayer");
                    video_mode = 1;
                }
                break;
            }
            case 2:{ // 退出
                printf("VideoPlay Exit\n");
                system("killall -9 mplayer");
                return 0;
            }
            default:{
                printf("VideoPlay Error\n");
                break;
            }
        }
    }
    while (choice != 0);

    return 0;
}