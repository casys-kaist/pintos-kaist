# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(close-normal) begin
(close-normal) open "sample.txt"
(close-normal) close "sample.txt"
(close-normal) end
close-normal: exit(0)
EOF
pass;
