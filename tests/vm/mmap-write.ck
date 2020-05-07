# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-write) begin
(mmap-write) create "sample.txt"
(mmap-write) open "sample.txt"
(mmap-write) mmap "sample.txt"
(mmap-write) compare read data against written data
(mmap-write) end
EOF
pass;
