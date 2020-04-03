# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(create-null) begin
create-null: exit(-1)
EOF
pass;
