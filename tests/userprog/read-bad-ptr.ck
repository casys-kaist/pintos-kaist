# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(read-bad-ptr) begin
(read-bad-ptr) open "sample.txt"
(read-bad-ptr) end
read-bad-ptr: exit(0)
EOF
(read-bad-ptr) begin
(read-bad-ptr) open "sample.txt"
read-bad-ptr: exit(-1)
EOF
pass;
