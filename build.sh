#!/bin/bash

sudo pacman -S ncurses
gcc main.c -lncurses
./a.out