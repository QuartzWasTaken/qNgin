#!/bin/bash

clear
gcc *.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lcjson -Wall
./a.out