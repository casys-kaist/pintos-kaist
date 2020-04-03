# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(fork-boundary) begin
(fork-boundary) child run
child-simple: exit(54)
(fork-boundary) fork
(fork-boundary) wait
(fork-boundary) end
fork-boundary: exit(0)
EOF
pass;
