# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(page-linear) begin
(page-linear) initialize
(page-linear) read pass
(page-linear) read/modify/write pass one
(page-linear) read/modify/write pass two
(page-linear) read pass
(page-linear) end
EOF
pass;
