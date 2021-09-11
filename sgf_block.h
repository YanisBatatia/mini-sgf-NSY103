//
// Created by yanis on 2021-09-08.
//
#include "sgf_types.h"

#ifndef PROJET_C_SGF_BLOCK_H
#define PROJET_C_SGF_BLOCK_H


void read_block(int n, BLOCK* bloc);

void write_block(int n, BLOCK* b);

void write_in_block(int n, char data_size, char* data, int decallage);


#endif //PROJET_C_SGF_BLOCK_H
