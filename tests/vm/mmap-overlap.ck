# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-overlap) begin
(mmap-overlap) open "zeros" once
(mmap-overlap) mmap "zeros"
(mmap-overlap) open "zeros" again
(mmap-overlap) try to mmap "zeros" again
(mmap-overlap) end
EOF
pass;
