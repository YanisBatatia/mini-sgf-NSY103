//
// Created by yanis on 2021-09-08.
//
#include "sgf_types.h"

#ifndef PROJET_C_SGF_BLOCK_H
#define PROJET_C_SGF_BLOCK_H

int init_sgf_disk(char* name);

void read_block(int n, BLOCK* bloc);

void write_block(int n, BLOCK* b);

long get_disk_size();

#endif //PROJET_C_SGF_BLOCK_H
