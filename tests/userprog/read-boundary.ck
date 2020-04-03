# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(read-boundary) begin
(read-boundary) open "sample.txt"
(read-boundary) end
read-boundary: exit(0)
EOF
pass;
