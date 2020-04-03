# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(read-zero) begin
(read-zero) open "sample.txt"
(read-zero) end
read-zero: exit(0)
EOF
pass;
