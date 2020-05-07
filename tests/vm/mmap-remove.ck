# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-remove) begin
(mmap-remove) open "sample.txt"
(mmap-remove) mmap "sample.txt"
(mmap-remove) remove "sample.txt"
(mmap-remove) try to open "sample.txt"
(mmap-remove) create "another"
(mmap-remove) end
EOF
pass;
