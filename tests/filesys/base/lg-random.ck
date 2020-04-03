# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(lg-random) begin
(lg-random) create "bazzle"
(lg-random) open "bazzle"
(lg-random) write "bazzle" in random order
(lg-random) read "bazzle" in random order
(lg-random) close "bazzle"
(lg-random) end
EOF
pass;
