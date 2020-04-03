# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(exec-bad-ptr) begin
(exec-bad-ptr) end
exec-bad-ptr: exit(0)
EOF
(exec-bad-ptr) begin
exec-bad-ptr: exit(-1)
EOF
pass;
