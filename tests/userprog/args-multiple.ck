# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(args) begin
(args) argc = 5
(args) argv[0] = 'args-multiple'
(args) argv[1] = 'some'
(args) argv[2] = 'arguments'
(args) argv[3] = 'for'
(args) argv[4] = 'you!'
(args) argv[5] = null
(args) end
args-multiple: exit(0)
EOF
pass;
