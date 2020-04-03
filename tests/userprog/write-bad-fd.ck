# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(write-bad-fd) begin
(write-bad-fd) end
write-bad-fd: exit(0)
EOF
(write-bad-fd) begin
write-bad-fd: exit(-1)
EOF
pass;
