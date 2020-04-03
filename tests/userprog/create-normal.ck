# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(create-normal) begin
(create-normal) create quux.dat
(create-normal) end
create-normal: exit(0)
EOF
pass;
