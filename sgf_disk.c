//
// Created by yanis on 2021-09-09.
//

#include "sgf_disk.h"

static struct HARD_DISK {
    FILE*   file;
    long     size; // disk size in block
    int     exist;
    char    nom[32];
} dd = {NULL, 0, 0, 0, ""};


int init_sgf_disk(char* name){

    FILE* file;
    long size;
    int X = 1024 * 1000;
    file = fopen(name, "wb");
    dd.file = file;
    ftruncate(fileno(file), X);
    size = (ftell(file) / BLOCK_SIZE);
    dd.size = size;
    dd.exist = 1;
    strcpy(dd.nom, name);
    fclose(file);

    return (1);
}

long get_disk_size()
{
    if (!dd.exist) init_sgf_disk("Disk0.bin");

    return (dd.size);
}