# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(fork-read) begin
(fork-read) open "sample.txt"
(fork-read) child run
(fork-read) Child: pintos is funny!
(fork-read) end
child: exit(0)
(fork-read) Parent success
(fork-read) end
fork-read: exit(0)
EOF
pass;
