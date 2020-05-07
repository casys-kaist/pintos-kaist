# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_USER_FAULTS => 1, [<<'EOF']);
(mmap-inherit) begin
(mmap-inherit) open "sample.txt"
(mmap-inherit) mmap "sample.txt"
(mmap-inherit) exec "child-inherit"
(child-inherit) begin
child-inherit: exit(-1)
(mmap-inherit) checking that mmap'd file still has same data
(mmap-inherit) end
mmap-inherit: exit(0)
EOF
pass;
