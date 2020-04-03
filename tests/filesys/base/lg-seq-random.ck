# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(lg-seq-random) begin
(lg-seq-random) create "nibble"
(lg-seq-random) open "nibble"
(lg-seq-random) writing "nibble"
(lg-seq-random) close "nibble"
(lg-seq-random) open "nibble" for verification
(lg-seq-random) verified contents of "nibble"
(lg-seq-random) close "nibble"
(lg-seq-random) end
EOF
pass;
