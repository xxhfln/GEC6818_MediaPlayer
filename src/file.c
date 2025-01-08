#include "file.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int getVideoFiles(const char *path)
{
    struct dirent *entry;
    DIR *dp;

    memset(video_files, '\0', sizeof(video_files));
    video_num = 0;

    // 打开video目录
    dp = opendir(path);
    if (dp == NULL){
        perror("opendir Error\n");
        return -1;
    }
    char copy_path[MAX_FILENAME_LENGTH] = {'\0'};
    int path_len = strlen(path);
    strcpy(copy_path, path);
    if (path[path_len - 1] != '/') {
        copy_path[path_len] = '/';
    }

    // 读取目录内容
    while((entry = readdir(dp)) && video_num < MAX_FILES){
        size_t len = strlen(entry->d_name);

        // 检查文件是否以 .avi 结尾
        char temp[MAX_FILENAME_LENGTH] = {'\0'};
        strcpy(temp, copy_path);
        if (len > 4 && strcmp(entry->d_name + len - 4, ".avi") == 0) {
            video_files[video_num] = (char *)malloc(len + 1 + strlen(copy_path));
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
    // for (int i = 0; i < video_num;i++){
    //     printf("File %d:%s\n", i, video_files[i]);
    // }

    return 0;
}

int getPhotoFiles(const char *path)
{
    struct dirent *entry;
    DIR *dp;

    memset(photo_files, '\0', sizeof(photo_files));
    photo_num = 0;

    // 打开video目录
    dp = opendir(path);
    if (dp == NULL){
        perror("opendir Error\n");
        return -1;
    }
    char copy_path[MAX_FILENAME_LENGTH] = {'\0'};
    int path_len = strlen(path);
    strcpy(copy_path, path);
    if (path[path_len - 1] != '/') {
        copy_path[path_len] = '/';
    }

    // 读取目录内容
    while((entry = readdir(dp)) && photo_num < MAX_FILES){
        size_t len = strlen(entry->d_name);

        // 检查文件是否以 .bmp 结尾
        char temp[MAX_FILENAME_LENGTH] = {'\0'};
        strcpy(temp, copy_path);
        if (len > 4 && strcmp(entry->d_name + len - 4, ".bmp") == 0) {
            photo_files[photo_num] = (char *)malloc(len + 1 + strlen(copy_path));
            if (photo_files[photo_num] == NULL){
                perror("malloc Error\n");
                closedir(dp);
                return -1;
            }

            strcat(temp, entry->d_name);
            int now_len = strlen(temp);
            strncpy(photo_files[photo_num], temp, now_len);
            // printf("after temp len:%d", strlen(temp));
            photo_files[photo_num][now_len] = '\0'; // 确保以'\0'结尾
            ++photo_num;
        }
    }
    closedir(dp);
    // for (int i = 0; i < photo_num;i++){
    //     printf("Photo File %d:%s\n", i, photo_files[i]);
    // }

    return 0;
}

int newFolder(const char *dir_name)
{
    if (mkdir(dir_name,0777) == -1){
        perror("make directory failed\n");
        return -1;
    }
    printf("Directory '%s' created successfully\n", dir_name);
    return 0;
}
