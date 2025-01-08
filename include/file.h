#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 256

char *video_files[MAX_FILES];
int video_num;
char *photo_files[MAX_FILES];
int photo_num;

int getVideoFiles(const char *path);
int getPhotoFiles(const char *path);
int newFolder(const char *dir_name);

#endif