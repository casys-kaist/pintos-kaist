# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(dup2-simple) open "sample.txt"
(dup2-simple) first dup2()
(dup2-simple) Parent success
dup2-simple: exit(0)
EOF
pass;
