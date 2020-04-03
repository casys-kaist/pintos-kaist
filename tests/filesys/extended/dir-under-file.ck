# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(dir-under-file) begin
(dir-under-file) create "abc"
(dir-under-file) mkdir "abc" (must return false)
(dir-under-file) end
EOF
pass;
