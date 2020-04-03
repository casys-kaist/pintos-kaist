# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_USER_FAULTS => 1, [<<'EOF']);
(bad-read2) begin
bad-read2: exit(-1)
EOF
pass;
