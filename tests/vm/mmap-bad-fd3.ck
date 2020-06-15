# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(mmap-bad-fd3) begin
(mmap-bad-fd3) try to mmap stdout
(mmap-bad-fd3) end
mmap-bad-fd3: exit(0)
EOF
(mmap-bad-fd3) begin
(mmap-bad-fd3) try to mmap stdout
mmap-bad-fd3: exit(-1)
EOF
pass;
