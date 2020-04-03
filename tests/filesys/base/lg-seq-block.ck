# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(lg-seq-block) begin
(lg-seq-block) create "noodle"
(lg-seq-block) open "noodle"
(lg-seq-block) writing "noodle"
(lg-seq-block) close "noodle"
(lg-seq-block) open "noodle" for verification
(lg-seq-block) verified contents of "noodle"
(lg-seq-block) close "noodle"
(lg-seq-block) end
EOF
pass;
