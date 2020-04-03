# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(write-boundary) begin
(write-boundary) open "sample.txt"
(write-boundary) end
write-boundary: exit(0)
EOF
pass;
