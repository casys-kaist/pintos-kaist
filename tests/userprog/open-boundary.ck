# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(open-boundary) begin
(open-boundary) open "sample.txt"
(open-boundary) end
open-boundary: exit(0)
EOF
pass;
