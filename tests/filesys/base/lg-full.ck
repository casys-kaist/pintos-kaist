# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(lg-full) begin
(lg-full) create "quux"
(lg-full) open "quux"
(lg-full) writing "quux"
(lg-full) close "quux"
(lg-full) open "quux" for verification
(lg-full) verified contents of "quux"
(lg-full) close "quux"
(lg-full) end
EOF
pass;
