cmake_minimum_required(VERSION 3.17)
project(DevoirSGF_SGF C)

set(CMAKE_C_STANDARD 99)


add_executable(DevoirSGF_SGF sgf_base.c sgf_disk.c sgf_fat.c sgf_inode.c sgf-io.c)

target_link_libraries(DevoirSGF_SGF m)
