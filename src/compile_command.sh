#!/bin/bash

gcc -D__KERNEL__ -D_GNU_SOURCE -DNR_CPUS=2 -DRUN -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -O2 -I ../include/ -I ../empty_includes/ -I ../empty_includes_arch/ combined_source.c -c -o combined_source.o
