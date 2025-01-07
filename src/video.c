#include "file.h"
#include "main.h"
#include "show_bmp.h"
#include "touch.h"
#include <stdio.h>
#include <stdlib.h>


void *getVideoCommand(char* video_command,int width, int height, char *filepath) {
    sprintf(video_command,
            "mplayer -slave -quiet -input file=/fifo -geometry 0:0 -zoom -x %d -y %d -loop 0 "
            "-framedrop -cache 8192 -lavdopts lowres=1:fast:skiploopfilter=all %s &",
            width,
            height,
            filepath);
}

int VideoPlay(int width, int height)
{
    show_bmp("./picture/zanting.bmp", p_lcd, 0, 400);

    // 打开视频文件
    int now_video_num = 0;
    char video_command[255];
    system("killall -9 mplayer");
    getVideoCommand(video_command,width,height,video_files[now_video_num]);
    system(video_command);

    // 操作视频
    int posx_, posy_;
    int choice;
    int video_mode = 1;
    do {
        int nTouch = project_touch(&posx_, &posy_);
        if (nTouch == 0){
            // choice = 1; // 暂停或继续视频
            choice = VideoTouch(posx_, posy_);
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
                    show_bmp("./picture/jixu.bmp", p_lcd, 0, 400);
                    video_mode = 0;
                } else {
                    printf("继续播放\n");
                    system("killall -SIGCONT mplayer");
                    show_bmp("./picture/zanting.bmp", p_lcd, 0, 400);
                    video_mode = 1;
                }
                break;
            }
            case 2:{ // 退出
                printf("VideoPlay Exit\n");
                system("killall -9 mplayer");
                return 0;
            }
            case 3:{ // 上一首
                if (now_video_num == 0){
                    now_video_num = video_num;
                }
                now_video_num -= 1;
                system("killall -9 mplayer");
                getVideoCommand(video_command, 800, 400, video_files[now_video_num]);
                system(video_command);
                break;
            }
            case 4:{ // 下一首
                if (now_video_num == video_num - 1){
                    now_video_num = -1;
                }
                now_video_num += 1;
                system("killall -9 mplayer");
                getVideoCommand(video_command, 800, 400, video_files[now_video_num]);
                system(video_command);
                break;
            }
            case 5:{ // 忽略无用操作
                break;
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
