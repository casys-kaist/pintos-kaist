# -*- perl -*-
use strict;
use warnings;
use tests::tests;
use tests::random;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(grow-seq-lg) begin
(grow-seq-lg) create "testme"
(grow-seq-lg) open "testme"
(grow-seq-lg) writing "testme"
(grow-seq-lg) close "testme"
(grow-seq-lg) open "testme" for verification
(grow-seq-lg) verified contents of "testme"
(grow-seq-lg) close "testme"
(grow-seq-lg) end
EOF
pass;
