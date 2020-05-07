# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-ro) begin
(mmap-ro) open "large.txt"
(mmap-ro) mmap "large.txt" with writable=0
(mmap-ro) about to write into read-only mmap'd memory
EOF
pass;
