#!/bin/sh

# compile
gcc -o convert ui.c countries.c server.c -lcjson -lncurses 

# run
./convert
