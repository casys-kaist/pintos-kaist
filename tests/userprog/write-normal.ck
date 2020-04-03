# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(write-normal) begin
(write-normal) create "test.txt"
(write-normal) open "test.txt"
(write-normal) end
write-normal: exit(0)
EOF
pass;
