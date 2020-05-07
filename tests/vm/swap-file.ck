# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(swap-file) begin
(swap-file) open "large.txt"
(swap-file) mmap "large.txt"
(swap-file) end
EOF
pass;
