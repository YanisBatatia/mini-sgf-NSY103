//
// Created by yanis on 2021-09-09.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "sgf_disk.h"
#include "sgf_types.h"

static struct HARD_DISK {
    FILE*   file;
    long     size; // disk size in block
    int     exist;
    char    nom[32];
} dd = {NULL, 0, 0, ""};


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

void write_in_block(int n, char data_size, char* data, int decallage)
{
    if (!dd.exist) init_sgf_disk("Disk0.bin");

    if (n < 0  ||  n >= dd.size)
    {
        fprintf(stderr, "sgf-disk: write_block: n° de bloc incorrect.");
    }

    if (fseek(dd.file, ((n - 1) * BLOCK_SIZE) + decallage, SEEK_SET) == 0)
        if (BLOCK_SIZE == fwrite(data, 1, data_size, dd.file))
        {
            fflush(dd.file);
            fprintf(stdout, "write block %d\n", n);
        }
}

long get_disk_size()
{
    if (dd.exist){
        return (dd.size);
    }
}

void init_sgf_disk(char* name){

    FILE* file;
    long size;
    int X = 1024 * 1000;
    file = fopen(name, "wb");
    dd.file = file;
    ftruncate(fileno(file), X);
    fseek(file, 0, SEEK_END);
    size = (ftell(file) / BLOCK_SIZE);
    dd.size = size;
    dd.exist = 1;
    strcpy(dd.nom, name);
    fclose(file);

}

