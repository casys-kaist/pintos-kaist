# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF', <<'EOF']);
(open-bad-ptr) begin
(open-bad-ptr) end
open-bad-ptr: exit(0)
EOF
(open-bad-ptr) begin
open-bad-ptr: exit(-1)
EOF
pass;
