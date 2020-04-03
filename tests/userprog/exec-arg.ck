# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(exec-arg) begin
(exec-arg) I'm your father
(args) begin
(args) argc = 2
(args) argv[0] = 'child-args'
(args) argv[1] = 'childarg'
(args) argv[2] = null
(args) end
exec-arg: exit(0)
EOF
pass;
