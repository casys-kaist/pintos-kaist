# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(grow-sparse) begin
(grow-sparse) create "testfile"
(grow-sparse) open "testfile"
(grow-sparse) seek "testfile"
(grow-sparse) write "testfile"
(grow-sparse) close "testfile"
(grow-sparse) open "testfile" for verification
(grow-sparse) verified contents of "testfile"
(grow-sparse) close "testfile"
(grow-sparse) end
EOF
pass;
