#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 256

char *video_files[MAX_FILES];
int video_num;

int getVideoFiles(const char *path);

#endif