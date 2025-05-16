/******************   ******************/
// @Author: Isaiah Isaiah@buaa.edu.cn
// @Date: 2025-04-21 16:43:06
// @LastEditors: Isaiah Isaiah@buaa.edu.cn
// @LastEditTime: 2025-05-16 11:31:30
// @FilePath: \prj_convert\dataConverter.c
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


void process_file_bin(const char *input_file, const char *output_file);
void process_file_int(const char *input_file, const char *output_file);
void process_file_float(const char *input_file, const char *output_file);
uint8_t str2num(char *data, char *num);


// 打印帮助信息
void print_help(const char *prog_name) {
    printf("lab2bin: datafile convert tools\n\n");
    printf("Usage: %s [options]\n", prog_name);
    printf("Options:\n");
    printf("  -h, --help             Show this help message\n");
    printf("  -v, --version          Show the version\n");
    printf("  -i, --input <file>     Specify input file\n");
    printf("  -o, --output <file>    Specify output file\n");
    printf("  -m, --mode <mode>      Specify data mode (bin, char, int, float)\n");
    
}

int main(int argc, char *argv[]) 
{
    static struct option long_options[] = {
        {"help",     no_argument,       0, 'h'},
        {"version",  no_argument,       0, 'v'},
        {"input",   required_argument, 0, 'i'},
        {"output",   required_argument, 0, 'o'},
        {"mode",   required_argument, 0, 'm'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;
    char *input_file = NULL;
    char *output_file = NULL;
    char *data_mode = NULL;
    while((opt = getopt_long(argc, argv, "hvi:o:m:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'h': // --help 或 -h
                // printf("Usage: %s --input <file> --output <file> --version --help\n", argv[0]);
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
            case 'm': // --mode 或 -m
                data_mode = optarg;
                break;
            case '?':
                // 处理未知选项或缺少参数的情况
                if (optopt == 'i' || optopt == 'o' || optopt == 'm') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
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
        printf("options start with - or --\n");
        printf("Use -h or --help for usage information.\n");
        return 1;
    }   

    // 打印结果
    if (input_file) {
        printf("Input file: %s\n", input_file);
    }
    if (output_file) {
        printf("Output file: %s\n", output_file);
    }
    if (input_file != NULL && output_file == NULL) {
        char *default_output_file = calloc(strlen(input_file) + 5, sizeof(char));
        strcpy(default_output_file, input_file);
        printf("Default output file: %s\n", default_output_file);
        char *dot_position = strrchr(default_output_file, '.');
        printf("dot_position: %s\n", dot_position);
        if (dot_position != NULL) {
            strcpy(dot_position, ".bin");
        } else {
            strcat(default_output_file, ".bin");
        }
        printf("Default output file: %s\n", default_output_file);
        output_file = default_output_file;
        // free(default_output_file);
        printf("Output file not specified, using default: %s\n", output_file);
    }
    
    if (data_mode != NULL) {
        printf("Data mode: %s\n", data_mode);
    } else {
        data_mode = "float";
        printf("Data mode not specified, using default: %s\n", data_mode);
    }

    switch(data_mode[0]) {
        case 'b':
            printf("Data mode: bin\n");
            process_file_bin(input_file, output_file);
            break;
        case 'c':
            printf("Data mode: char\n");
            break;
        case 'i':
            printf("Data mode: int\n");
            process_file_int(input_file, output_file);
            
    FILE *bin = fopen(output_file, "rb");
    if (!bin) {
        printf("文件%s打开失败\n", output_file);
        exit(1);
    }
    uint16_t read_data;
    uint16_t *dataArrayCheck = malloc(2070 * sizeof(uint16_t));

    for (int i = 0; i < 2070; i++) {
        fread(&read_data, sizeof(uint16_t), 1, bin);
        dataArrayCheck[i] = read_data;
        if(i>2050) {
            printf("数据：%.4d\n", read_data);
        }
    }
    fclose(bin);
            break;
        case 'f':
            printf("Data mode: float\n");
            process_file_float(input_file, output_file);
                // rewind(bin);
    // FILE *bin = fopen(output_file, "rb");
    // if (!bin) {
    //     printf("文件%s打开失败\n", output_file);
    //     exit(1);
    // }
    // double read_data;
    // double *dataArrayCheck = malloc(20 * sizeof(double));

    // for (int i = 0; i < 20; i++) {
    //     fread(&read_data, sizeof(double), 1, bin);
    //     dataArrayCheck[i] = read_data;
    //     if(i<20) {
    //         printf("数据：%.20f\n", read_data);
    //     }
    // }
    // fclose(bin);
            break;
        default:
            printf("Unknown data mode, using default: int\n");
    }

    return 0;
}


// 处理文件
void process_file_bin(const char *input_file, const char *output_file) 
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

// 处理文件
void process_file_int(const char *input_file, const char *output_file) 
{
    FILE *csv = fopen(input_file, "r+");
    FILE *bin = fopen(output_file, "wb");
    if (!csv) {
        printf("文件%s打开失败\n", input_file);
        exit(1);
    }
    if (!bin) {
        printf("文件%s打开失败\n", output_file);
        fclose(csv);
        exit(1);
    }
    
    fseek(csv, -1, SEEK_END);
    // char last_char = fgetc(csv);
    if(fgetc(csv) != '\n') {
        fseek(csv, 0, SEEK_END);
        fputc('\n', csv);
        fflush(csv);
        printf("已在文件末尾添加换行符\n");
    } else {
        printf("文件末尾已有换行符\n");
    }
    fseek(csv, 0, SEEK_SET);
    

    printf("文件处理:\n");
    
    char line[MAX_LINE_LENGTH];
    size_t max_cols = 0;
    size_t data_count = 0;
    size_t line_count = 0;
    while (fgets(line, MAX_LINE_LENGTH, csv)) {
        line_count++;
        char *ptr = line;
        size_t col_count = 0;
        while (*ptr != '\0') {
            while (*ptr == ' '|| *ptr == '\a') {
                ptr++;
            }
            while (*ptr == ','||*ptr == '\n') {
                ptr++;
                data_count++;
                col_count++;
                // printf("\n");
            }
            if (*ptr == '\0') break;
            // printf("当前字符：%c ，字符编码：%x ，地址：%p\n",*ptr, *ptr, ptr);

            ptr++;
        }   

        if (col_count > max_cols) max_cols = col_count;
    }

    printf("行数: %zu, 列数: %zu, 数据个数: %zu\n", line_count, max_cols, data_count);
    // if(line_count * max_cols != data_count) {
    //     printf("非对齐数据，行数和列数不匹配\n");
    // }

    rewind(csv);

    
    // char *strArray[data_count];
    uint16_t *dataArray = malloc(data_count * sizeof(uint16_t));
    uint16_t ret = 0;
    size_t idx = 0;
    // printf("数据转换:\n");
    while (fgets(line, MAX_LINE_LENGTH, csv)) {
        // printf("当前行：%s", line);
        char *ptr = line;
        while (*ptr != '\0') {
            ret = strtol(ptr, &ptr, 10);
            dataArray[idx] = ret;
            // sprintf(strArray[idx], "%d", ret);
            // printf("数据：%.20f\n", ret);
            fwrite(&ret, sizeof(uint16_t), 1, bin);
            idx++;
            
            while (*ptr == ' ' || *ptr == ','|| *ptr == '\a' || *ptr == '\n') ptr++;
            if (*ptr == '\0') break;
        }
    }
    
    // // rewind(bin);
    // fflush(bin);
    // fseek(bin, 0, SEEK_SET);
    // double read_data;
    // double *dataArrayCheck = malloc(data_count * sizeof(double));

    // for (int i = 0; i < data_count; i++) {
    //     fread(&read_data, sizeof(double), 1, bin);
    //     dataArrayCheck[i] = read_data;
    //     if(i<20) {
    //         printf("数据：%.20f\n", read_data);
    //     }
    // }

    fclose(csv);
    fclose(bin);
}



// 处理文件
void process_file_float(const char *input_file, const char *output_file) 
{
    FILE *csv = fopen(input_file, "r+");
    FILE *bin = fopen(output_file, "wb");
    if (!csv) {
        printf("文件%s打开失败\n", input_file);
        exit(1);
    }
    if (!bin) {
        printf("文件%s打开失败\n", output_file);
        fclose(csv);
        exit(1);
    }
    
    fseek(csv, -1, SEEK_END);
    // char last_char = fgetc(csv);
    if(fgetc(csv) != '\n') {
        fseek(csv, 0, SEEK_END);
        fputc('\n', csv);
        fflush(csv);
        printf("已在文件末尾添加换行符\n");
    } else {
        printf("文件末尾已有换行符\n");
    }
    fseek(csv, 0, SEEK_SET);
    

    printf("文件处理:\n");
    
    char line[MAX_LINE_LENGTH];
    size_t max_cols = 0;
    size_t data_count = 0;
    size_t line_count = 0;
    while (fgets(line, MAX_LINE_LENGTH, csv)) {
        line_count++;
        char *ptr = line;
        size_t col_count = 0;
        while (*ptr != '\0') {
            while (*ptr == ' '|| *ptr == '\a') {
                ptr++;
            }
            while (*ptr == ','||*ptr == '\n') {
                ptr++;
                data_count++;
                col_count++;
                // printf("\n");
            }
            if (*ptr == '\0') break;
            // printf("当前字符：%c ，字符编码：%x ，地址：%p\n",*ptr, *ptr, ptr);

            ptr++;
        }   

        if (col_count > max_cols) max_cols = col_count;
    }

    printf("行数: %zu, 列数: %zu, 数据个数: %zu\n", line_count, max_cols, data_count);
    // if(line_count * max_cols != data_count) {
    //     printf("非对齐数据，行数和列数不匹配\n");
    // }

    rewind(csv);

    
    // char *strArray[data_count];
    double *dataArray = malloc(data_count * sizeof(double));
    double ret = 0;
    size_t idx = 0;
    // printf("数据转换:\n");
    while (fgets(line, MAX_LINE_LENGTH, csv)) {
        // printf("当前行：%s", line);
        char *ptr = line;
        while (*ptr != '\0') {
            ret = strtod(ptr, &ptr);
            dataArray[idx] = ret;
            // sprintf(strArray[idx], "%d", ret);
            // printf("数据：%.20f\n", ret);
            fwrite(&ret, sizeof(double), 1, bin);
            idx++;
            
            while (*ptr == ' ' || *ptr == ','|| *ptr == '\a' || *ptr == '\n') ptr++;
            if (*ptr == '\0') break;
        }
    }
    
    // // rewind(bin);
    // fflush(bin);
    // fseek(bin, 0, SEEK_SET);
    // double read_data;
    // double *dataArrayCheck = malloc(data_count * sizeof(double));

    // for (int i = 0; i < data_count; i++) {
    //     fread(&read_data, sizeof(double), 1, bin);
    //     dataArrayCheck[i] = read_data;
    //     if(i<20) {
    //         printf("数据：%.20f\n", read_data);
    //     }
    // }

    fclose(csv);
    fclose(bin);
}

