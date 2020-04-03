# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(write-zero) begin
(write-zero) open "sample.txt"
(write-zero) end
write-zero: exit(0)
EOF
pass;
