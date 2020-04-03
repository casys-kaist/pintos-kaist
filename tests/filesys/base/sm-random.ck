# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(sm-random) begin
(sm-random) create "bazzle"
(sm-random) open "bazzle"
(sm-random) write "bazzle" in random order
(sm-random) read "bazzle" in random order
(sm-random) close "bazzle"
(sm-random) end
EOF
pass;
