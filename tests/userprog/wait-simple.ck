# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(wait-simple) begin
(child-simple) run
child-simple: exit(81)
(wait-simple) wait(exec()) = 81
(wait-simple) end
wait-simple: exit(0)
EOF
pass;
