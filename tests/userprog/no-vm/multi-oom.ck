# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_USER_FAULTS => 1, IGNORE_EXIT_CODES => 1, [<<'EOF']);
(multi-oom) begin
(multi-oom) Spawned at least 10 children.
(multi-oom) success. Program forked 10 iterations.
(multi-oom) end
EOF
pass;
