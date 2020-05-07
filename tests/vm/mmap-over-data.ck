# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-over-data) begin
(mmap-over-data) open "sample.txt"
(mmap-over-data) try to mmap over data segment
(mmap-over-data) end
EOF
pass;
