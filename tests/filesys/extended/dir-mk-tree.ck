# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(dir-mk-tree) begin
(dir-mk-tree) creating /0/0/0/0 through /3/2/2/3...
(dir-mk-tree) open "/0/2/0/3"
(dir-mk-tree) close "/0/2/0/3"
(dir-mk-tree) end
EOF
pass;
