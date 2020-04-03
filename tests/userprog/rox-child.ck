# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(rox-child) begin
(rox-child) open "child-rox"
(rox-child) read "child-rox"
(rox-child) write "child-rox"
(rox-child) exec "child-rox 1"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(rox-child) write "child-rox"
(rox-child) end
rox-child: exit(0)
EOF
pass;
