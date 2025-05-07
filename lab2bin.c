/******************   ******************/
// @Author: Isaiah Isaiah@buaa.edu.cn
// @Date: 2025-04-21 16:43:06
// @LastEditors: Isaiah Isaiah@buaa.edu.cn
// @LastEditTime: 2025-05-07 16:56:36
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


void process_file(const char *input_file, const char *output_file) ;



// 打印帮助信息
void print_help(const char *prog_name) {
    printf("lab2bin: datafile convert tools\n\n");
    printf("Usage: %s [options]\n", prog_name);
    printf("Options:\n");
    printf("  -h, --help             Show this help message\n");
    printf("  -v, --version          Show the version\n");
    printf("  -i, --input <file>     Specify input file\n");
    printf("  -o, --output <file>    Specify output file\n");
}

int main(int argc, char *argv[]) 
{
    static struct option long_options[] = {
        {"help",     no_argument,       0, 'h'},
        {"version",  no_argument,       0, 'v'},
        {"input",   required_argument, 0, 'i'},
        {"output",   required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;
    const char *input_file = NULL;
    const char *output_file = NULL;
    while((opt = getopt_long(argc, argv, "hvi:o:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'h': // --help 或 -h
                printf("Usage: %s --input <file> --output <file> --version --help\n", argv[0]);
                print_help(argv[0]);
                return 0;
            case 'v': // --version 或 -v
                printf("Version 1.0\n");
                return 0;
            case 'i': // --input 或 -i
                input_file = optarg;
                break;
            case 'o': // --output 或 -o
                output_file = optarg;
                break;
            case '?':
                // 处理未知选项或缺少参数的情况
                if (optopt == 'i') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } 
                else if (optopt == 'o') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option: %s\n", argv[optind - 1]);
                }
                return 1;
            default:
                print_help(argv[0]);
                return 1;
        }
    }
    // 处理非选项参数
    if (optind < argc) {
        printf("Non-option arguments: ");
        while (optind < argc) {
            printf("%s ", argv[optind++]);
        }
        printf("\n");
    }   

    // 打印结果
    if (input_file) {
        printf("Input file: %s\n", input_file);
    }
    if (output_file) {
        printf("Output file: %s\n", output_file);
    }
    
    process_file(input_file, output_file);

    return 0;
}



// 处理文件
void process_file(const char *input_file, const char *output_file) 
{
    // 写入 bin 文件
    csv_to_bin(input_file, output_file);

    // 从 bin 文件读取数据
    static uint8_t array[ROWS][PACKED_COLS];  // 注意较大内存使用
    bin_to_array(output_file, array);

    // 示例输出第1行前20位
    printf("第1行前20位:\n");
    for (int i = 0; i < 150; i++) {
        printf("%d ", array[15543][i]);
    }
    printf("\n");
}


