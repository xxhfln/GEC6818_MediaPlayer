#include "main.h"
#include "file.h"
#include "show_bmp.h"
#include "slow_slide.h"

int main(int argc,char* argv[])
{
    // 初始化
    project_init();

    // 开机界面
    show_1152000bmp("./picture/qidong.bmp", p_lcd);
    sleep(3);
    
    // 滑动解锁界面
    show_1152000bmp("./picture/jiesuo.bmp", p_lcd);
    huadong_exec();


    for (int i = 0; i < video_num; i++) {
        printf("File %d: %s\n", i + 1, video_files[i]);
    }
    // 主界面
    project_ui();

    // 程序销毁
    project_destroy();

    return 0;
}