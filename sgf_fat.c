//
// Created by yanis on 2021-09-09.
//

#include "math.h"
#include "sgf_fat.h"
#include "sgf_types.h"
#include "sgf_disk.h"

#define FREE (-1);
#define RESERVED (-2);
#define INODE (-3);
#define EOF (-4);

typedef struct {
    int size_in_block;
    int* block_contents;
} FAT;

static FAT fat = {0, NULL};

void init_sgf_fat(){

    int fat_size_in_octet;
    int disk_size_in_block = get_disk_size();
    fat_size_in_octet = disk_size_in_block * sizeof(int);
    fat.size_in_block = (int) ceil((fat_size_in_octet / (double) BLOCK_SIZE));
    fat_size_in_octet =  fat.size_in_block * BLOCK_SIZE;

    fat.block_contents[0] = RESERVED;

    for (i=1; i<fat.size_in_block; i++){
        fat.block_contents[i] = RESERVED;
    }

    int j = 1 + fat.size_in_block;

    for (;j < disk_size_in_block; j++){
        fat.block_contents[j] = FREE;
    }


}