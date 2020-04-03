# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(dir-vine) begin
(dir-vine) creating many levels of files and directories...
(dir-vine) removing all but top 10 levels of files and directories...
(dir-vine) end
EOF
pass;
