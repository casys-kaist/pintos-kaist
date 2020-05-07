# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(pt-grow-stack) begin
(pt-grow-stack) cksum: 3424492700
(pt-grow-stack) end
EOF
pass;
