#include "file.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

int getVideoFiles(const char *path)
{
    struct dirent *entry;
    DIR *dp;

    // 打开video目录
    dp = opendir(path);
    if (dp == NULL){
        perror("opendir Error\n");
        return -1;
    }

    // 读取目录内容
    while((entry = readdir(dp)) && video_num < MAX_FILES){
        size_t len = strlen(entry->d_name);

        // 检查文件是否以 .avi 结尾
        char temp[MAX_FILENAME_LENGTH] = {'\0'};
        strcpy(temp, "./video/");
        if (len > 4 && strcmp(entry->d_name + len - 4, ".avi") == 0) {
            video_files[video_num] = (char *)malloc(len + 1 + strlen("./video/"));
            if (video_files[video_num] == NULL){
                perror("malloc Error\n");
                closedir(dp);
                return -1;
            }

            strcat(temp, entry->d_name);
            int now_len = strlen(temp);
            strncpy(video_files[video_num], temp, now_len);
            // printf("after temp len:%d", strlen(temp));
            video_files[video_num][now_len] = '\0'; // 确保以'\0'结尾
            ++video_num;
        }
    }
    closedir(dp);

    return 0;
}