//
// Created by yanis on 2021-09-09.
//

#include "math.h"
#include "sgf_fat.h"
#include "sgf_types.h"
#include "sgf_disk.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define FREE        (-1)
#define RESERVED    (-2)
#define INODE       (-3)
#define EOFI        (-4)


typedef struct {
    int size_in_block;
    int* block_contents;
} FAT;

static FAT fat = {0, NULL};

void save_in_fat (int n )
{
    int valeur = fat.block_contents[ n ] ;
    int element_fat_size = BLOCK_SIZE / sizeof(int);
    int fat_block_position = (n / element_fat_size) + 1;
    int decallage = n - (element_fat_size * (fat_block_position - 1));

    printf("decallage : %d \n", decallage);
    char data[sizeof(valeur)];
    sprintf(data,"%d", valeur);

    write_in_block(fat_block_position, sizeof(int), data, decallage);

/*
    int k;
    BLOCK *blocks;

    for(k = 1; (k < fat.size_in_block); k++){
        write_block(k , & blocks[k]);
    }
*/
}

void set_in_fat (int n, int valeur)
{
    int disk_size_in_block = get_disk_size();

    if (n < 0  ||  n >= disk_size_in_block)
        fprintf(stderr,"Problem in set_in_fat : index out of bound");

    assert(
            ((valeur) == FREE) ||
            ((valeur) == INODE) ||
            ((valeur) == EOFI) ||
            ((valeur) >= 0 && (valeur) < disk_size_in_block)
    );

    fat.block_contents[ n ] = valeur;
    save_in_fat(n);
}


int get_in_fat (int i)
{
    int disk_size_in_block = get_disk_size();

    if (i < 0  ||  i >= disk_size_in_block)
        fprintf(stderr,"Problem in get_in_fat %d", i);

    return fat.block_contents[ i ];
}

int block_allocation (void)
{
    int k;
    int disk_size_in_block = get_disk_size();

    for(k = 0; k < disk_size_in_block; k++) {
        if (fat.block_contents[k] == FREE) {
            return (k);
        }
    }

    return (-1);
}


void init_sgf_fat(){

    int fat_size_in_octet;
    int disk_size_in_block = (int) get_disk_size();

    GBLOCK super_block;
    BLOCK *blocks;

    fat_size_in_octet = disk_size_in_block * sizeof(int);
    fat.size_in_block = (int) ceil((fat_size_in_octet / (double) BLOCK_SIZE));
    fat_size_in_octet =  fat.size_in_block * BLOCK_SIZE;


    fat.block_contents = malloc(fat_size_in_octet);
    fat.block_contents[0] = RESERVED;

    int i;
    for (i=1; i < fat.size_in_block + 1; i++){
        fat.block_contents[i] = RESERVED;
    }

    int j = 1 + fat.size_in_block;

    for (;j < disk_size_in_block; j++){
        fat.block_contents[j] = FREE;
    }

    int k;
    for (k=0; (fat.block_contents[k] != FREE ); k++);
    int adr_racine = k;

    super_block.racine.adr_racine = adr_racine;
    write_block(0, & super_block.data);

    for (i=1; i<fat.size_in_block; i++){
        write_block(i, & blocks[i]);
    }

}
