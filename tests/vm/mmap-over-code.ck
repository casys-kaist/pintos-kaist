# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-over-code) begin
(mmap-over-code) open "sample.txt"
(mmap-over-code) try to mmap over code segment
(mmap-over-code) end
EOF
pass;
