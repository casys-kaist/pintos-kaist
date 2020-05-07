# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-misalign) begin
(mmap-misalign) open "sample.txt"
(mmap-misalign) try to mmap at misaligned address
(mmap-misalign) end
EOF
pass;
