// #include"save_load.h"
#include "main.h"
#include <stddef.h>
#include <stdio.h>

int save_user_data() {
    FILE *f = fopen("user_data.dat", "wb");
    if (f == NULL) {
        printf("保存数据失败\n");
        return 0;
    }

    char temp[2];
    sprintf(temp, "%d", user_count);
    size_t written = fwrite(temp, 1, 1, f);
    
    fwrite(users, sizeof(User), user_count, f);

    fclose(f);
    return 1;
}

int load_user_data()
{
    FILE *f = fopen("user_data.dat", "rb");
    if (f == NULL) {
        return 0;  // 文件不存在，说明没有用户数据
    }
    char num;
    fread(&num, 1, 1, f);    
    user_count = (int)(num - '0');
    fread(users, sizeof(User), user_count, f);


    fclose(f);
    return 1;
}