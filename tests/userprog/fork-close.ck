# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(fork-close) begin
(fork-close) open "sample.txt"
(fork-close) child run
(fork-close) end
child: exit(0)
(fork-close) Parent success
(fork-close) end
fork-close: exit(0)
EOF
pass;
