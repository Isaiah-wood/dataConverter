/******************   ******************/
// @Author: Isaiah Isaiah@buaa.edu.cn
// @Date: 2025-04-21 17:16:45
// @LastEditors: Isaiah Isaiah@buaa.edu.cn
// @LastEditTime: 2025-05-07 11:15:56
// @FilePath: \prj_convert\convert.c
// @Description: 
/******************   ******************/
// convert.c
#include <stdio.h>
#include "convert.h"

#define COLS 1200
#define COMPRESSED_COLS (COLS / 8)

// 私有函数：打包8位为1字节
uint8_t pack_bits(uint8_t *bits) {
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
        result |= (bits[i] & 1) << (7 - i);
    }
    return result;
}

// 私有函数：解包1字节为8位字符串
void unpack_byte(uint8_t byte, uint8_t *out_bits) {
    for (int i = 0; i < 8; i++) {
        out_bits[i] = (byte >> (7 - i)) & 1;
    }
}

// 公有函数：CSV转压缩BIN文件
void csv_to_bin(const char *csv_path, const char *bin_path) {
    FILE *csv = fopen(csv_path, "r");
    FILE *bin = fopen(bin_path, "wb");
    if (!csv) {
        printf("文件%s打开失败\n", csv_path);
        exit(1);
    }
    if (!bin) {
        printf("文件%s打开失败\n", bin_path);
        fclose(csv);
        exit(1);
    }

    uint8_t bits[8];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < PACKED_COLS; j++) {
            for (int k = 0; k < 8; k++) {
                int val;
                fscanf(csv, "%d,", &val);  // 读取逗号分隔的0/1
                bits[k] = (uint8_t)(val & 1);
            }
            uint8_t packed = pack_bits(bits);
            fwrite(&packed, sizeof(uint8_t), 1, bin);
        }
    }

    fclose(csv);
    fclose(bin);
    printf("CSV 转 BIN 完成\n");
}

// 公有函数：读取BIN文件到数组
// int bin_to_array(const char *bin_file, unsigned char array[][COMPRESSED_COLS], int rows) {
//     FILE *fp = fopen(bin_file, "rb");
//     if (!fp) {
//         perror("读取BIN失败");
//         return -1;
//     }

//     for (int i = 0; i < rows; i++) {
//         if (fread(array[i], 1, COMPRESSED_COLS, fp) != COMPRESSED_COLS) {
//             perror("读取行数据失败");
//             fclose(fp);
//             return -1;
//         }
//     }

//     fclose(fp);
//     return 0;
// }
void bin_to_array(const char *bin_path, uint8_t array[ROWS][PACKED_COLS]) {
    FILE *bin = fopen(bin_path, "rb");
    if (!bin) {
        printf("无法打开bin文件\n");
        exit(1);
    }

    uint8_t byte;
    // uint8_t bits[8];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < PACKED_COLS; j++) {
            fread(&byte, sizeof(uint8_t), 1, bin);
            // unpack_byte(byte, bits);
            for (int k = 0; k < 8; k++) {
                array[i][j] = byte;
            }
        }
    }

    fclose(bin);
    printf("BIN 文件已解压为 0/1 矩阵\n");
}
