# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(mmap-bad-off) begin
(mmap-bad-off) open "large.txt"
(mmap-bad-off) try to mmap invalid offset
(mmap-bad-off) end
mmap-bad-off: exit(0)
EOF
pass;
