# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(exec-once) begin
(exec-once) I'm your father
(child-simple) run
exec-once: exit(81)
EOF
pass;
