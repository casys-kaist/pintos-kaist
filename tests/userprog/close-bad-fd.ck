# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(close-bad-fd) begin
(close-bad-fd) end
close-bad-fd: exit(0)
EOF
(close-bad-fd) begin
close-bad-fd: exit(-1)
EOF
pass;
