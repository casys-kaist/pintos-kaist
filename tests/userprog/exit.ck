# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(exit) begin
exit: exit(57)
EOF
pass;
