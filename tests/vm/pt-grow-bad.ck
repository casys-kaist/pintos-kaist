# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_USER_FAULTS => 1, [<<'EOF']);
(pt-grow-bad) begin
pt-grow-bad: exit(-1)
EOF
pass;
