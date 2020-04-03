# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(sm-seq-random) begin
(sm-seq-random) create "nibble"
(sm-seq-random) open "nibble"
(sm-seq-random) writing "nibble"
(sm-seq-random) close "nibble"
(sm-seq-random) open "nibble" for verification
(sm-seq-random) verified contents of "nibble"
(sm-seq-random) close "nibble"
(sm-seq-random) end
EOF
pass;
