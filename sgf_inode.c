//
// Created by yanis on 2021-09-09.
//

#include <string.h>
#include <stdio.h>
#include "sgf_types.h"
#include "sgf_fat.h"
#include "sgf_disk.h"
#include "sgf_inode.h"

#define FREE        (-1)
#define RESERVED    (-2)
#define INODE       (-3)
#define EOFI        (-4)


int find_inode(const char* name)
{
    GBLOCK b;
    int j;

    read_block(0, & b.data);
    int adr = b.racine.adr_racine;

    while (adr != EOFI)
    {
        read_block(adr, &b.data);
        for(j = 0; j < DIR_SIZE; j++)
            if (b.dir[j].block_position > 0)
                if (strcmp(b.dir[j].filename, name) == 0)
                    return (b.dir[j].block_position);
        adr = get_in_fat(adr);
    }

    return (-1);
}


int add_inode (const char* name, int block_inode)
{
    int  oldinode, padr, nadr;
    int j, nj;
    GBLOCK  b;

    if (strlen(name) >= 29) {
        return (-1);
    }

    read_block(0, & b.data);
    int adr = b.racine.adr_racine;


    nadr = nj = -1;
    while (adr != EOFI)
    {
        read_block(adr, &b.data);
        for(j = 0; j < DIR_SIZE; j++)
            if (b.dir[j].block_position > 0)
                if (strcmp(b.dir[j].filename, name) == 0)
                {
                    oldinode = b.dir[j].block_position;
                    b.dir[j].block_position = block_inode;
                    write_block(adr, & b.data);
                    return (oldinode);
                }
                else ;
            else nadr = adr, nj = j;
        padr = adr;
        adr = get_in_fat(adr);
    }

    if (nadr != -1) {
        read_block(nadr, & b.data);
        b.dir[nj].block_position = block_inode;
        strcpy(b.dir[nj].filename, name);
        write_block(nadr, & b.data);
        return (-1);
    }

    /** Allouer un nouveau bloc pour le répertoire **/
    adr = block_allocation();
    if (adr < 0) return (-1);

    /** Initialiser ce nouveau bloc **/
    for(j = 0; j < DIR_SIZE; j++)
        b.dir[j].block_position = 0;

    /** Utiliser la 1ere entree de ce bloc **/
    b.dir[0].block_position = block_inode;
    strcpy(b.dir[0].filename, name);
    write_block(adr, & b.data);

    /** Mettre à jour la FAT **/
    set_in_fat(adr, EOFI);
    set_in_fat(padr, adr);

    return (-1);
}

void delete_inode (const char* name)
{
    GBLOCK b;
    int j;

    read_block(0, & b.data);
    int adr = b.racine.adr_racine;

    while (adr != EOFI)
    {
        read_block(adr, & b.data);
        for(j = 0; j < DIR_SIZE; j++)
            if (b.dir[j].block_position > 0)
                if (strcmp(b.dir[j].filename, name) == 0)
                {
                    b.dir[j].block_position = 0;
                    write_block(adr, & b.data);
                    return ;
                }
        adr = get_in_fat(adr);
    }

}


void list_directory (void)
{
    GBLOCK b, b2;
    int j;

    read_block(0, & b.data);
    int adr = b.racine.adr_racine;

    while (adr != EOFI)
    {
        read_block(adr, &b.data);
        for(j = 0; j < DIR_SIZE; j++){
            if (b.dir[j].block_position > 0)
            {
                read_block(b.dir[j].block_position,&b2.data);
                printf("%s : Taille : %ld\n",b.dir[j].filename, b2.inode.size_file);
            }
        }
        adr = get_in_fat(adr);
    }
}
