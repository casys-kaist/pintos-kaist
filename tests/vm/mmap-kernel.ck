# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(mmap-kernel) begin
(mmap-kernel) open "sample.txt"
(mmap-kernel) try to mmap over kernel 0
(mmap-kernel) try to mmap over kernel 1
(mmap-kernel) try to mmap over kernel 2
(mmap-kernel) end
mmap-kernel: exit(0)
EOF
pass;
