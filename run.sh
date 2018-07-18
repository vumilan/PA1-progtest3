#!/bin/bash

#gcc -fsanitize=address -g main.c
gcc -Wall -pedantic -Wno-long-long -O3 main.c
#gcc -O3 main.c
