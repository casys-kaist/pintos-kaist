# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(create-bad-ptr) begin
create-bad-ptr: exit(-1)
EOF
pass;
