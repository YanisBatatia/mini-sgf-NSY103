//
// Created by yanis on 2021-09-09.
//

#ifndef MINI_SGF_NSY103_SGF_DISK_H
#define MINI_SGF_NSY103_SGF_DISK_H

#include "sgf_types.h"

void init_sgf_disk(char* name);

long get_disk_size();

void read_block(int n, BLOCK* bloc);

void write_block(int n, BLOCK* b);

void write_in_block(int n, char data_size, char* data, int decallage);



#endif //MINI_SGF_NSY103_SGF_DISK_H
