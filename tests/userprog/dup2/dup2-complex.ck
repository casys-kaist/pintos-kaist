# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(dup2-complex) open "sample.txt"
(dup2-complex) open "sample.txt"
(dup2-complex) first dup2()
Pintos is funny
child: exit(110)
(dup2-complex) Parent success
dup2-complex: exit(0)
EOF
pass;
