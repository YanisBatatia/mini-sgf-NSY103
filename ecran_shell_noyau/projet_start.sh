#!/bin/bash

gcc projet_ecran.c -o projet_ecran
gcc projet_shell.c -o projet_shell

gnome-terminal -- /bin/sh -c './projet_ecran;' 
gnome-terminal -- /bin/sh -c './projet_shell;'
