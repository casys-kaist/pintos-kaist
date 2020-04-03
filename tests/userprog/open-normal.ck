# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(open-normal) begin
(open-normal) end
open-normal: exit(0)
EOF
pass;
