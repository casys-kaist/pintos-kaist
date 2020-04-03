# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(dir-over-file) begin
(dir-over-file) mkdir "abc"
(dir-over-file) create "abc" (must return false)
(dir-over-file) end
EOF
pass;
