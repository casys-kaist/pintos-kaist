# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(mmap-exit) begin
(child-mm-wrt) begin
(child-mm-wrt) create "sample.txt"
(child-mm-wrt) open "sample.txt"
(child-mm-wrt) mmap "sample.txt"
(child-mm-wrt) end
(mmap-exit) open "sample.txt" for verification
(mmap-exit) verified contents of "sample.txt"
(mmap-exit) close "sample.txt"
(mmap-exit) end
EOF
pass;
