# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(create-bound) begin
(create-bound) create("quux.dat"): 1
(create-bound) end
create-bound: exit(0)
EOF
pass;
