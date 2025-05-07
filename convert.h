/******************   ******************/
// @Author: Isaiah Isaiah@buaa.edu.cn
// @Date: 2025-04-21 17:16:53
// @LastEditors: Isaiah Isaiah@buaa.edu.cn
// @LastEditTime: 2025-05-07 11:16:44
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

// 公有接口函数声明
void csv_to_bin(const char *csv_file, const char *bin_file);
// int bin_to_array(const char *bin_file, unsigned char array[][150], int rows);
void bin_to_array(const char *bin_path, unsigned char array[ROWS][PACKED_COLS]);

#endif
