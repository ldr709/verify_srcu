#!/bin/bash

# TODO: Maybe --memory-leak-check
#cbmc_check_opts="--bounds-check --div-by-zero-check --pointer-check --signed-overflow-check"
#cbmc_check_opts="-32"
cbmc_check_opts="-32 --pointer-check"
cbmc ${cbmc_check_opts} -DFORCE_FAILURE -D__KERNEL__ -D_GNU_SOURCE -DNR_CPUS=2 -I ../include/ -I ../empty_includes/ -I ../empty_includes_arch/ combined_source.c
