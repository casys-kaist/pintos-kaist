# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(mmap-zero-len) begin
(mmap-zero-len) create "sample.txt"
(mmap-zero-len) open "sample.txt"
(mmap-zero-len) try to mmap zero length
(mmap-zero-len) end
mmap-zero-len: exit(0)
EOF
(mmap-zero-len) begin
(mmap-zero-len) create "sample.txt"
(mmap-zero-len) open "sample.txt"
(mmap-zero-len) try to mmap zero length
mmap-zero-len: exit(-1)
EOF
pass;
