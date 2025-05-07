/******************   ******************/
// @Author: Isaiah Isaiah@buaa.edu.cn
// @Date: 2025-04-21 16:43:06
// @LastEditors: Isaiah Isaiah@buaa.edu.cn
// @LastEditTime: 2025-05-07 15:39:59
// @FilePath: \prj_convert\lab2bin.c
// @Description: 
/******************   ******************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include "getopt.h" 
#else
#include <unistd.h>
#include <getopt.h>
#endif


#include "convert.h"


void print_help();
void process_file(const char *filename);

// uint8_t pack_bits(uint8_t *bits);
// void csv_to_bin(const char *csv_path, const char *bin_path);
// void unpack_byte(uint8_t byte, uint8_t *out_bits);
// void bin_to_array(const char *bin_path, uint8_t array[ROWS][PACKED_COLS]);



int main(int argc, char *argv[]) 
{

    // 检查参数数量
    if (argc < 2) {
        printf("错误：缺少参数。使用 -h 查看帮助信息。\n");
        return 1;
    }

    // 处理参数
    if (strcmp(argv[1], "-h") == 0) {
        print_help();
    } else if (strcmp(argv[1], "-f") == 0) {
        if (argc < 3) {
            printf("错误：-f 参数后需要指定文件名。\n");
            return 1;
        }
        process_file(argv[2]);
    } else {
        printf("错误：未知参数 '%s'。使用 -h 查看帮助信息。\n", argv[1]);
        return 1;
    }

    // const char *csv_file = "PatternLib.csv";
    // const char *bin_file = "PatternLib.bin";

    // // 写入 bin 文件
    // csv_to_bin(csv_file, bin_file);

    // // 从 bin 文件读取数据
    // static uint8_t array[ROWS][PACKED_COLS];  // 注意较大内存使用
    // bin_to_array(bin_file, array);

    // // 示例输出第1行前20位
    // printf("第1行前20位:\n");
    // for (int i = 0; i < 150; i++) {
    //     printf("%d ", array[15543][i]);
    // }
    // printf("\n");

    return 0;
}

// 打印帮助信息
void print_help() {
    printf("lab2bin - 数据库文件处理工具\n\n");
    printf("功能:\n");
    printf("  将.csv文件转换为.bin文件\n");
    printf("用法:\n");
    printf("  lab2bin -h             显示此帮助信息\n\n");
    printf("  lab2bin -f xxx.csv    读取并处理指定的数据库文件\n");
    printf("示例:\n");
    printf("  lab2bin -f data.csv\n");
}



// 处理文件
void process_file(const char *filename) {

    // const char *csv_file = "PatternLib.csv";
    // const char *bin_file = "PatternLib.bin";

    char *fullfilename = (char *)malloc(strlen(filename) + 5); // 4个字符 + 1个结束符   
    fullfilename = strcpy(fullfilename, filename);


    char *csv_file = strcat(fullfilename, ".csv");
    char *bin_file = strcat(fullfilename, ".bin");

    // 写入 bin 文件
    csv_to_bin(csv_file, bin_file);

    // 从 bin 文件读取数据
    static uint8_t array[ROWS][PACKED_COLS];  // 注意较大内存使用
    bin_to_array(bin_file, array);

    // 示例输出第1行前20位
    printf("第1行前20位:\n");
    for (int i = 0; i < 150; i++) {
        printf("%d ", array[15543][i]);
    }
    printf("\n");
}


