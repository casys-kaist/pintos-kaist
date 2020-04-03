# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(fork-multiple) begin
(fork-multiple) child run
child: exit(4)
(fork-multiple) Parent: child exit status is 4
(fork-multiple) child run
child: exit(5)
(fork-multiple) Parent: child exit status is 5
(fork-multiple) child run
child: exit(6)
(fork-multiple) Parent: child exit status is 6
(fork-multiple) child run
child: exit(7)
(fork-multiple) Parent: child exit status is 7
(fork-multiple) end
fork-multiple: exit(0)
EOF
pass;
