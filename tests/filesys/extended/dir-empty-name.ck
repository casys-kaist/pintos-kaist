# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(dir-empty-name) begin
(dir-empty-name) mkdir "" (must return false)
(dir-empty-name) end
EOF
pass;
