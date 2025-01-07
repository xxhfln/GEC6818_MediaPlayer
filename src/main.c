#include "main.h"
#include "show_bmp.h"
#include "slow_slide.h"

int main(int argc,char* argv[])
{
    // 初始化
    project_init();
    
    // 滑动解锁界面
    show_1152000bmp("./picture/jiesuo.bmp", p_lcd);
    huadong_exec();

    // 主界面
    project_ui();

    // 程序销毁
    project_destroy();

    return 0;
}