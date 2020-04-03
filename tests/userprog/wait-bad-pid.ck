# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(wait-bad-pid) begin
(wait-bad-pid) end
wait-bad-pid: exit(0)
EOF
(wait-bad-pid) begin
wait-bad-pid: exit(-1)
EOF
pass;
