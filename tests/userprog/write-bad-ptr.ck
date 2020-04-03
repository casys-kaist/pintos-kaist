# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(write-bad-ptr) begin
(write-bad-ptr) open "sample.txt"
(write-bad-ptr) end
write-bad-ptr: exit(0)
EOF
(write-bad-ptr) begin
(write-bad-ptr) open "sample.txt"
write-bad-ptr: exit(-1)
EOF
pass;
