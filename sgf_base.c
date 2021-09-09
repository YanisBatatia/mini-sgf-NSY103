//
// Created by yanis on 2021-09-06.
//
#include "sgf_disk.h"
#include "sgf_block.h"
#include "sgf_fat.h"

int main() {
    init_sgf_disk("Disk0.bin");
    init_sgf_fat();
    int first_empty_block = block_allocation();
    set_in_fat(first_empty_block,14);
}
