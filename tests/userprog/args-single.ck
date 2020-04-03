# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(args) begin
(args) argc = 2
(args) argv[0] = 'args-single'
(args) argv[1] = 'onearg'
(args) argv[2] = null
(args) end
args-single: exit(0)
EOF
pass;
