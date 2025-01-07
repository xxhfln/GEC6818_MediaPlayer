#include "main.h"

int main(int argc,char* argv[])
{
    // 初始化
    project_init();
    
    // 主界面
    project_ui();

    // 程序销毁
    project_destroy();

    return 0;
}