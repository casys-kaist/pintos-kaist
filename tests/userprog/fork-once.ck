# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(fork-once) begin
(fork-once) child run
child: exit(81)
(fork-once) Parent: child exit status is 81
(fork-once) end
fork-once: exit(0)
EOF
pass;
