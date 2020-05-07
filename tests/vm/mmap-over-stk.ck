# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-over-stk) begin
(mmap-over-stk) open "sample.txt"
(mmap-over-stk) try to mmap over stack segment
(mmap-over-stk) end
EOF
pass;
