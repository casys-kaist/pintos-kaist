# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(rox-simple) begin
(rox-simple) open "rox-simple"
(rox-simple) read "rox-simple"
(rox-simple) try to write "rox-simple"
(rox-simple) end
rox-simple: exit(0)
EOF
pass;
