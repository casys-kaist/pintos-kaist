# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(pt-bad-read) begin
(pt-bad-read) open "sample.txt"
pt-bad-read: exit(-1)
EOF
pass;
