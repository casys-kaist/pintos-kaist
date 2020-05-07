# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(pt-write-code2) begin
(pt-write-code2) open "sample.txt"
pt-write-code2: exit(-1)
EOF
pass;
