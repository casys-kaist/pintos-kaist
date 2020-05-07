# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(mmap-bad-fd) begin
(mmap-bad-fd) try to mmap invalid fd
(mmap-bad-fd) end
mmap-bad-fd: exit(0)
EOF
(mmap-bad-fd) begin
(mmap-bad-fd) try to mmap invalid fd
mmap-bad-fd: exit(-1)
EOF
pass;
