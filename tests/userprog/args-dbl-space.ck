# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(args) begin
(args) argc = 3
(args) argv[0] = 'args-dbl-space'
(args) argv[1] = 'two'
(args) argv[2] = 'spaces!'
(args) argv[3] = null
(args) end
args-dbl-space: exit(0)
EOF
pass;
