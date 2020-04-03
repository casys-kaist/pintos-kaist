# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(create-long) begin
(create-long) create("x..."): 0
(create-long) end
create-long: exit(0)
EOF
pass;
