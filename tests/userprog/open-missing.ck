# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(open-missing) begin
(open-missing) end
open-missing: exit(0)
EOF
pass;
