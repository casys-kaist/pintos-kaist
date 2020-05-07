# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(pt-big-stk-obj) begin
(pt-big-stk-obj) cksum: 3256410166
(pt-big-stk-obj) end
EOF
pass;
