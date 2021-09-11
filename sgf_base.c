//
// Created by yanis on 2021-09-06.
//
#include <stdio.h>
#include "sgf_disk.h"
#include "sgf_block.h"
#include "sgf_fat.h"

int main() {
    init_sgf_disk("Disk0.bin");
    init_sgf_fat();
    int first_empty_block = block_allocation();
    /*printf("%d \n",first_empty_block);*/
    set_in_fat(300,14);
    for (int i = 0; i < 350; ++i) {
        printf("%d ", get_in_fat(i));
    }

    printf("\n %d ", get_in_fat(300));
}
