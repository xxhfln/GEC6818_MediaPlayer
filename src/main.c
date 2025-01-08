#include "main.h"
#include "file.h"
#include "manage_login.h"
#include "show_bmp.h"
#include "slow_slide.h"
#include <unistd.h>

int main(int argc,char* argv[])
{
    // 初始化
    project_init();

    // 开机界面
    // show_1152000bmp("./picture/qidong.bmp", p_lcd);
    // sleep(3);
    // int count = 0;
    char *gif[4] = {"./picture/gif1.bmp", "./picture/gif2.bmp", "./picture/gif3.bmp", "./picture/gif4.bmp"};
    for (int j = 0; j < 4;j++){
        show_1152000bmp(gif[j], p_lcd);
        sleep(1);
    }
    

    while(1){
        // 滑动解锁界面
        show_1152000bmp("./picture/jiesuo.bmp", p_lcd);
        huadong_exec();
        show_1152000bmp("./picture/wait.bmp", p_lcd);

        // 登陆
        memset(user_path, '\0', sizeof(user_path));
        memset(user_picture_path, '\0', sizeof(user_path));
        memset(user_video_path, '\0', sizeof(user_path));
        int ret = manage_login();
        if (ret == -1){
            project_destroy();
            return 0;
        }
        show_1152000bmp("./picture/login.bmp", p_lcd);
        sleep(2);

        // 主界面
        int ret_ = project_ui();
    }
    // 程序销毁
    project_destroy();

    return 0;
}