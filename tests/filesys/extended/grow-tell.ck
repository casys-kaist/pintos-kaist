# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(grow-tell) begin
(grow-tell) create "foobar"
(grow-tell) open "foobar"
(grow-tell) writing "foobar"
(grow-tell) close "foobar"
(grow-tell) open "foobar" for verification
(grow-tell) verified contents of "foobar"
(grow-tell) close "foobar"
(grow-tell) end
EOF
pass;
