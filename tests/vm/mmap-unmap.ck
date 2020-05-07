# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(mmap-unmap) begin
(mmap-unmap) open "sample.txt"
(mmap-unmap) mmap "sample.txt"
(mmap-unmap) memory is readable 540884285
(mmap-unmap) memory is readable 540888381
mmap-unmap: exit(-1)
EOF
pass;
