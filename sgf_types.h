//
// Created by yanis on 2021-09-08.
//

#ifndef PROJET_C_SGF_TYPES_H
#define PROJET_C_SGF_TYPES_H

#include <stddef.h>

#define BLOCK_SIZE (128)
typedef char BLOCK[ BLOCK_SIZE ];

typedef struct {
    int first_block;
    int final_block;
    size_t number_blocks; // en blocks
    size_t size_file; // en blocks
    int permissions[8];
} INODE;

typedef struct {
    char filename;
    int block_position;
} DIR;

#endif
