# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(args) begin
(args) argc = 1
(args) argv[0] = 'args-none'
(args) argv[1] = null
(args) end
args-none: exit(0)
EOF
pass;
