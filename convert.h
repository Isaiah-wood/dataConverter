/******************   ******************/
// @Author: Isaiah Isaiah@buaa.edu.cn
// @Date: 2025-04-21 17:16:53
// @LastEditors: Isaiah Isaiah@buaa.edu.cn
// @LastEditTime: 2025-05-12 20:04:24
// @FilePath: \prj_convert\convert.h
// @Description: 
/******************   ******************/
// convert.h
#ifndef CONVERT_H
#define CONVERT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define ROWS 15544
#define COLS 1200
#define PACKED_COLS (COLS / 8)  // 150
#define MAX_LINE_LENGTH 4096   // 可根据实际最长行长度酌情增大


typedef enum {
    DATA_MODE_UNDEFINED = 0,
    DATA_MODE_CHAR,
    DATA_MODE_INT,
    DATA_MODE_FLOAT
} data_mode_t;

// 公有接口函数声明
void csv_to_bin(const char *csv_file, const char *bin_file);
// int bin_to_array(const char *bin_file, unsigned char array[][150], int rows);
void bin_to_array(const char *bin_path, unsigned char array[ROWS][PACKED_COLS]);

#endif
