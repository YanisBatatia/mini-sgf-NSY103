//
// Created by yanis on 2021-09-09.
//

#ifndef DEVOIRSGF_SGF_SGF_INODE_H
#define DEVOIRSGF_SGF_SGF_INODE_H

int find_inode(const char* name);

int add_inode (const char* name, int block_inode);

void delete_inode (const char* name);

void list_directory (void);


#endif //DEVOIRSGF_SGF_SGF_INODE_H
