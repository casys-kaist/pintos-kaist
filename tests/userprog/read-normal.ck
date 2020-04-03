# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(read-normal) begin
(read-normal) open "sample.txt" for verification
(read-normal) verified contents of "sample.txt"
(read-normal) close "sample.txt"
(read-normal) end
read-normal: exit(0)
EOF
pass;
