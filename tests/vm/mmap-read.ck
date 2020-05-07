# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-read) begin
(mmap-read) open "sample.txt"
(mmap-read) mmap "sample.txt"
(mmap-read) end
EOF
pass;
