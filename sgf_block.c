//
// Created by yanis on 2021-09-08.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sgf_types.h"
#include "sgf_block.h"


int init_dir(){

    return (1);
}

void read_block(int n, BLOCK* bloc)
{

    if (fseek(dd.file, (n * BLOCK_SIZE), SEEK_SET) == 0)
        if (BLOCK_SIZE == fread(bloc, 1, BLOCK_SIZE, dd.file))
        {
            fprintf(stdout, "read block %d\n", n);
            return;
        }

}


void write_block(int n, BLOCK* b)
{
    if (!dd.exist) init_sgf_disk("Disk0.bin");

    if (n < 0  ||  n >= dd.size)
    {
        fprintf(stderr, "sgf-disk: write_block: n° de bloc incorrect.");
    }

    if (fseek(dd.file, (n * BLOCK_SIZE), SEEK_SET) == 0)
        if (BLOCK_SIZE == fwrite(b, 1, BLOCK_SIZE, dd.file))
        {
            fflush(dd.file);
            fprintf(stdout, "write block %d\n", n);
        }
}
