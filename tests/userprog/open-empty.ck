# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(open-empty) begin
(open-empty) end
open-empty: exit(0)
EOF
pass;
