# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(mmap-bad-fd2) begin
(mmap-bad-fd2) try to mmap stdin
(mmap-bad-fd2) end
mmap-bad-fd2: exit(0)
EOF
(mmap-bad-fd2) begin
(mmap-bad-fd2) try to mmap stdin
mmap-bad-fd2: exit(-1)
EOF
pass;
