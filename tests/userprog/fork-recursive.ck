# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(fork-recursive) begin
(fork-recursive) child run
(fork-recursive) child run
(fork-recursive) child run
(fork-recursive) child run
(fork-recursive) child run
(fork-recursive) child run
(fork-recursive) child run
(fork-recursive) child run
child: exit(10)
(fork-recursive) Parent: child exit status is 10
child: exit(10)
(fork-recursive) Parent: child exit status is 10
child: exit(9)
(fork-recursive) Parent: child exit status is 9
child: exit(8)
(fork-recursive) Parent: child exit status is 8
child: exit(7)
(fork-recursive) Parent: child exit status is 7
child: exit(6)
(fork-recursive) Parent: child exit status is 6
child: exit(5)
(fork-recursive) Parent: child exit status is 5
child: exit(4)
(fork-recursive) Parent: child exit status is 4
(fork-recursive) end
fork-recursive: exit(0)
EOF
pass;
