# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(exec-boundary) begin
(child-simple) run
child-simple: exit(81)
(exec-boundary) fork
(exec-boundary) wait
(exec-boundary) end
exec-boundary: exit(0)
EOF
pass;
