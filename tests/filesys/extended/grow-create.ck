# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(grow-create) begin
(grow-create) create "blargle"
(grow-create) open "blargle" for verification
(grow-create) verified contents of "blargle"
(grow-create) close "blargle"
(grow-create) end
EOF
pass;
