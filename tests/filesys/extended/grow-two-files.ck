# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(grow-two-files) begin
(grow-two-files) create "a"
(grow-two-files) create "b"
(grow-two-files) open "a"
(grow-two-files) open "b"
(grow-two-files) write "a" and "b" alternately
(grow-two-files) close "a"
(grow-two-files) close "b"
(grow-two-files) open "a" for verification
(grow-two-files) verified contents of "a"
(grow-two-files) close "a"
(grow-two-files) open "b" for verification
(grow-two-files) verified contents of "b"
(grow-two-files) close "b"
(grow-two-files) end
EOF
pass;
