# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(grow-seq-sm) begin
(grow-seq-sm) create "testme"
(grow-seq-sm) open "testme"
(grow-seq-sm) writing "testme"
(grow-seq-sm) close "testme"
(grow-seq-sm) open "testme" for verification
(grow-seq-sm) verified contents of "testme"
(grow-seq-sm) close "testme"
(grow-seq-sm) end
EOF
pass;
