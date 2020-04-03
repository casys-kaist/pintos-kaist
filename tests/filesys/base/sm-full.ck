# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(sm-full) begin
(sm-full) create "quux"
(sm-full) open "quux"
(sm-full) writing "quux"
(sm-full) close "quux"
(sm-full) open "quux" for verification
(sm-full) verified contents of "quux"
(sm-full) close "quux"
(sm-full) end
EOF
pass;
