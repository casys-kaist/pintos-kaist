# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(dir-rm-tree) begin
(dir-rm-tree) creating /0/0/0/0 through /3/2/2/3...
(dir-rm-tree) open "/0/2/0/3"
(dir-rm-tree) close "/0/2/0/3"
(dir-rm-tree) removing /0/0/0/0 through /3/2/2/3...
(dir-rm-tree) open "/3/0/2/0" (must return -1)
(dir-rm-tree) end
EOF
pass;
