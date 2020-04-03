# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(read-bad-fd) begin
(read-bad-fd) end
read-bad-fd: exit(0)
EOF
(read-bad-fd) begin
read-bad-fd: exit(-1)
EOF
pass;
