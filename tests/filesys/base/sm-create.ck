# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(sm-create) begin
(sm-create) create "blargle"
(sm-create) open "blargle" for verification
(sm-create) verified contents of "blargle"
(sm-create) close "blargle"
(sm-create) end
EOF
pass;
