//
// Created by yanis on 2021-09-08.
//

#ifndef PROJET_C_SGF_TYPES_H
#define PROJET_C_SGF_TYPES_H

#include <stddef.h>

#define BLOCK_SIZE (1024)
#define DIR_SIZE (BLOCK_SIZE / sizeof(DIR_ENTRY))

typedef char BLOCK[ BLOCK_SIZE ]; // DATA

typedef struct {
    int first_block;
    int final_block;
    size_t number_blocks; // en blocks
    size_t size_file; // en blocks
    int permissions[8];
} INODE;

typedef struct  {
    int racine; // Adresse du premier DIR
} SBLOCK; // BLOCK de definition systeme

typedef struct {
    char filename [28];
    int block_position;
} DIR_ENTRY;

typedef DIR_ENTRY DIR [DIR_SIZE]; // Repertoire

typedef union {
    RACINE racine;
    DIR dir;
    INODE inode;
    BLOCK data;
} BLOCK; // Block generique

#endif
