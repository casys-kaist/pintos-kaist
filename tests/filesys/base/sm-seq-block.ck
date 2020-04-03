# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(sm-seq-block) begin
(sm-seq-block) create "noodle"
(sm-seq-block) open "noodle"
(sm-seq-block) writing "noodle"
(sm-seq-block) close "noodle"
(sm-seq-block) open "noodle" for verification
(sm-seq-block) verified contents of "noodle"
(sm-seq-block) close "noodle"
(sm-seq-block) end
EOF
pass;
