#!/bin/bash

# Create a directory tree containing empty files with the same names as kernel
# headers.

rm -rf empty_includes/
mkdir empty_includes/
( cd linux_source/include/ && find . -type d '(' '!' -path '.' ')' -print0 ) | xargs -0 -I '{}' mkdir 'empty_includes/{}'
( cd linux_source/include/ && find . -name "*.h" -print0 ) | xargs -0 -I '{}' touch 'empty_includes/{}'

rm -rf empty_includes_arch/
mkdir empty_includes_arch/
# Just use x86's include tree. It shouldn't matter since they are empty files.
( cd linux_source/arch/x86/include/ && find . -type d '(' '!' -path '.' ')' -print0 ) | xargs -0 -I '{}' mkdir 'empty_includes_arch/{}'
( cd linux_source/arch/x86/include/ && find . -name "*.h" -print0 ) | xargs -0 -I '{}' touch 'empty_includes_arch/{}'

#Use the system errno.h
rm empty_includes/linux/errno.h
