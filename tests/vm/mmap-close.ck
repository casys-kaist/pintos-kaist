# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-close) begin
(mmap-close) open "sample.txt"
(mmap-close) mmap "sample.txt"
(mmap-close) end
EOF
pass;
