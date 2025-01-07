#include "main.h"
int k=0,flag=0;

//滑动解锁
int show_hua(int silde_x)
{
    //清除解锁进度的区域
    for(int y=400;y<430;y++)
    {
        for(int x=0;x<SCREEN_WIDTH;x++)
        {
            if(x>silde_x-50&&x<silde_x+50)
            {                               
                *(p_lcd+y*SCREEN_WIDTH+x) = 0x0000;//黑色填充，表示已经通过的部分
            }
            else//
            {
                *(p_lcd+y*SCREEN_WIDTH+x) = 0xffff;//白色填充，表示没有滑动的部分
            }
            if(x<=silde_x-50)
            {
                *(p_lcd+y*SCREEN_WIDTH+x) = 0x0000;//
            }          
        }
    }
    //滑动解锁需要有过程
    if(silde_x>=100&&silde_x<=200)
    {
        if(flag == 0 )
        {
            k++;
            flag++;
        }
    }
    if( silde_x>=300&&silde_x<=400)
    {
        if(flag == 1 )
        {
            k++;
            flag++;
        }
    }
    if( silde_x>=500&&silde_x<=600)
    {
        if(flag == 2 )
        {
            k++;
            flag++;
        }
    }
    if( silde_x>=700&&silde_x<=SCREEN_WIDTH)
    {
        if(flag == 3 )
        {
            k++;
            flag++;
        }
    }
   
    //判断是否解锁成功
    if(silde_x>=750&&k==4)
    {
        printf("解锁成功\n");
        for(int y=0;y<480;y++)
        {
            for(int x=0;x<SCREEN_WIDTH;x++)
            {          
                *(p_lcd+y*SCREEN_WIDTH+x) = 0x00ff;
            }
        }
        sleep(1);
        return 1;
    }
    return 0;
}

void huadong_exec()
{
    int posx, posy;
    int up_flag = 0;
    int ret = 0;
    while (1) {
        posx = 0;
        while (1) {
            read(fd_touch, &buf, sizeof(buf));

            if (buf.type==EV_ABS && buf.code==ABS_X){
                posx = buf.value;
            }
            if (buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 1){
                break; // 按下
            }
        }

        // project_touch(&posx, &posy);
        while ((ret = show_hua(posx)) == 0) {
            while(1){
                read(fd_touch, &buf, sizeof(buf));

                if (buf.type==EV_ABS && buf.code==ABS_X){
                    posx = buf.value;
                    break;
                }
                if (buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 0){
                    up_flag = 1;
                    break; // 松开
                }
            }
            if (up_flag == 1){
                show_hua(0);
                break;
            }
        };
        if (ret == 1){
            break;
        }
    }
}

