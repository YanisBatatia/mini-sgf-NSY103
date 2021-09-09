//
// Created by yanis on 2021-09-06.
//
#include <stdio.h>
#include "sgf_disk.h"
#include "sgf_fat.h"
#include "sgf_inode.h"
#include "sgf-io.h"

int main() {
    init_sgf_disk("Disk0.bin");
    init_sgf_fat();

    OFILE* file = sgf_open("test.txt", WRITE_MODE);
    sgf_puts(file, "FUCK le C");
    sgf_close(file);

    OFILE* Rfile = sgf_open("test.txt", READ_MODE);
    int c = sgf_getc(Rfile);
    printf("%d", c);
}
