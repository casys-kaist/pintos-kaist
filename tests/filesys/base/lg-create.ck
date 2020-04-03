# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(lg-create) begin
(lg-create) create "blargle"
(lg-create) open "blargle" for verification
(lg-create) verified contents of "blargle"
(lg-create) close "blargle"
(lg-create) end
EOF
pass;
