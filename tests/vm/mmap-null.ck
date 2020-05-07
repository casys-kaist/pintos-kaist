# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-null) begin
(mmap-null) open "sample.txt"
(mmap-null) try to mmap at address 0
(mmap-null) end
EOF
pass;
